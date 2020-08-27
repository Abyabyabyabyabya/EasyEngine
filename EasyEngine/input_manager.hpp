///
/// \file   input_manager.hpp
/// \brief  入力マネージャー定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/19
///             - ヘッダ追加
///             - InputManager 定義
///
#ifndef INCLUDED_EGEG_ILIB_INPUT_MANAGER_HEADER_
#define INCLUDED_EGEG_ILIB_INPUT_MANAGER_HEADER_

#include <memory>
#include <unordered_map>
#include <Windows.h>
#include "noncopyable.hpp"
#include "input_device.hpp"
#include "id.hpp"

namespace easy_engine {
class EasyEngine;

namespace i_lib {

/******************************************************************************

    InputManager

******************************************************************************/
///
/// \class  InputManager
/// \brief  入力マネージャー
///
///         このクラスへのアクセスは、EasyEngine::input()を使用してください。
///
class InputManager final : t_lib::Noncopyable<InputManager> {
public :
    friend EasyEngine;

    ~InputManager() = default;

    ///
    /// \brief  入力デバイスと接続
    ///
    ///         既に接続されている場合は、新しく追加せずに既にあるデバイスを返却します。
    ///
    /// \tparam DeviceTy : 接続する入力デバイス
    /// \tparam ArgTypes : 入力デバイスのコンストラクタに転送する引数型リスト
    /// \param[in] Args : 入力デバイスのコンストラクタに転送する引数リスト
    ///
    /// \return 接続した入力デバイスへのポインタ
    ///
    template <class DeviceTy, class ...ArgTypes>
    const DeviceTy* connect(ArgTypes&& ...Args) {
        if(auto* d = device<DeviceTy>()) return d;
        
        InputDevice* connected = devices_.emplace(
            t_lib::TypeIDGenerator<DeviceTy>{},
            std::make_unique<DeviceTy>(std::forward<ArgTypes>(Args)...)).first->second.get();
        return static_cast<const DeviceTy*>(connected);
    }

    ///
    /// \brief  入力デバイスの接続を解除
    ///
    /// \tparam DeviceTy : 接続を解除するデバイス
    ///
    template <class DeviceTy>
    void disconnect() noexcept(noexcept(devices_.erase(t_lib::TypeIDGenerator<DeviceTy>{}))) {
        devices_.erase(t_lib::TypeIDGenerator<DeviceTy>{});
    }

    ///
    /// \brief  接続されているデバイスを取得
    ///
    ///         指定されたデバイスが接続されていない場合はnullptrを返却します。
    ///
    /// \tparam DeviceTy : 取得するデバイス
    ///
    /// \return デバイスへのポインタ
    ///
    template <class DeviceTy>
    const DeviceTy* device() const {
        auto find_itr = devices_.find(t_lib::TypeIDGenerator<DeviceTy>{});

        if(find_itr==devices_.end()) return nullptr;
        return static_cast<const DeviceTy*>(find_itr->second.get());
    }

private :
    static std::unique_ptr<InputManager> create();      // EasyEngineクラスにより呼び出される関数
    void update();                                      // 上同 保持するデバイスをすべて更新する
    void keyEvent(UINT, WPARAM, LPARAM) const noexcept; // 上同 キーボードのイベントメッセージ処理

    InputManager() = default;

    std::unordered_map<uintptr_t, std::unique_ptr<InputDevice>> devices_;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_INPUT_MANAGER_HEADER_
// E0F
