
#include <cstdint>
#include <ratio>

namespace easy_engine {
namespace state {

#define EGEG_WINDOW_NAME "EasyEngine" // Window名
constexpr int kWindowWidth  = 1280; // ウィンドウ横幅
constexpr int kWindowHeight = 720;  // ウィンドウ縦幅
constexpr bool kWindowed    = true; // ウィンドウモード true:ウィンドウ　false:フルスクリーン
constexpr int kFPS          = 60;   // Frame Per Seconds : 1秒当たりのフレーム数
    
} // namespace state

template <class T>
constexpr T kWindowWidth = static_cast<T>(state::kWindowWidth);
template <class T>
constexpr T kWindowHeight = static_cast<T>(state::kWindowHeight);
template <class T>
constexpr T kFPS = static_cast<T>(state::kFPS);
template <class TimeUnit=std::milli, std::uintmax_t FPS=kFPS<std::uintmax_t>> 
constexpr std::intmax_t kTPF = // Time Per Frame : 1フレーム当たりの時間
  std::ratio_divide<std::ratio<1,FPS>, TimeUnit>::num/std::ratio_divide<std::ratio<1,FPS>, TimeUnit>::den;
} // namespace easy_engine
// EOF
