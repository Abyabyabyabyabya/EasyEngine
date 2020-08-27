
#include <cstdint>
#include <ratio>

namespace easy_engine {
namespace state {

#define EGEG_WINDOW_NAME "EasyEngine" // Window��
constexpr int kWindowWidth  = 1280; // �E�B���h�E����
constexpr int kWindowHeight = 720;  // �E�B���h�E�c��
constexpr bool kWindowed    = true; // �E�B���h�E���[�h true:�E�B���h�E�@false:�t���X�N���[��
constexpr int kFPS          = 60;   // Frame Per Seconds : 1�b������̃t���[����
    
} // namespace state

template <class T>
constexpr T kWindowWidth = static_cast<T>(state::kWindowWidth);
template <class T>
constexpr T kWindowHeight = static_cast<T>(state::kWindowHeight);
template <class T>
constexpr T kFPS = static_cast<T>(state::kFPS);
template <class TimeUnit=std::milli, std::uintmax_t FPS=kFPS<std::uintmax_t>> 
constexpr std::intmax_t kTPF = // Time Per Frame : 1�t���[��������̎���
  std::ratio_divide<std::ratio<1,FPS>, TimeUnit>::num/std::ratio_divide<std::ratio<1,FPS>, TimeUnit>::den;
} // namespace easy_engine
// EOF
