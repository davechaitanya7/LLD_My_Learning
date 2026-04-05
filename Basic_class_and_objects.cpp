#include <iostream>
#include <string>

struct EncoderConfiguration {
    int profile_token;
    std::string profile_name;

    EncoderConfiguration(int token = 0, const std::string &name = "")
        : profile_token(token), profile_name(name) {}
};

struct DecoderConfiguration {
    int profile_token;
    std::string profile_name;

    DecoderConfiguration(int token = 0, const std::string &name = "")
        : profile_token(token), profile_name(name) {}
};

class Profile {
private:
    int profile_token_;
    std::string profile_name_;

public:
    EncoderConfiguration video_encoder_configuration_;
    DecoderConfiguration video_decoder_configuration_;
    EncoderConfiguration audio_encoder_configuration_;
    DecoderConfiguration audio_decoder_configuration_;

    Profile(int token = 0, const std::string &name = "")
        : profile_token_(token), profile_name_(name),
          video_encoder_configuration_(0, ""),
          video_decoder_configuration_(0, ""),
          audio_encoder_configuration_(0, ""),
          audio_decoder_configuration_(0, "") {}

    void setProfileInfo(int token, const std::string &name) {
        profile_token_ = token;
        profile_name_ = name;
    }

    void print() const {
        std::cout << "Profile token: " << profile_token_ << "\n";
        std::cout << "Profile name: " << profile_name_ << "\n";
        std::cout << "Video encoder: " << video_encoder_configuration_.profile_name
                  << " (token=" << video_encoder_configuration_.profile_token << ")\n";
        std::cout << "Video decoder: " << video_decoder_configuration_.profile_name
                  << " (token=" << video_decoder_configuration_.profile_token << ")\n";
        std::cout << "Audio encoder: " << audio_encoder_configuration_.profile_name
                  << " (token=" << audio_encoder_configuration_.profile_token << ")\n";
        std::cout << "Audio decoder: " << audio_decoder_configuration_.profile_name
                  << " (token=" << audio_decoder_configuration_.profile_token << ")\n";
    }
};

class Camera {
private:
    int camera_id_;
    std::string camera_name_;
    Profile camera_profile_;

public:
    Camera(int id = 0, const std::string &name = "", const Profile &profile = Profile())
        : camera_id_(id), camera_name_(name), camera_profile_(profile) {}

    void setProfile(const Profile &profile) {
        camera_profile_ = profile;
    }

    void printInfo() const {
        std::cout << "Camera ID: " << camera_id_ << "\n";
        std::cout << "Camera name: " << camera_name_ << "\n";
        camera_profile_.print();
    }
};

int main() {
    Profile onvif_profile(1, "ONVIF_Profile_HD");
    onvif_profile.video_encoder_configuration_ = EncoderConfiguration(10, "H.264");
    onvif_profile.video_decoder_configuration_ = DecoderConfiguration(11, "H.264");
    onvif_profile.audio_encoder_configuration_ = EncoderConfiguration(20, "AAC");
    onvif_profile.audio_decoder_configuration_ = DecoderConfiguration(21, "AAC");

    Camera camera(1001, "ONVIF Camera", onvif_profile);
    camera.printInfo();

    return 0;
}
