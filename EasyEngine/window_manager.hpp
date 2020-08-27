///
/// \file   window_manager.hpp
/// \brief  ウィンドウマネージャークラス定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/25
///             - ヘッダ追加
///             - WindowManager 定義
///
/// \note   コールバック関数の登録解除について\n
///         現時点で必要性を感じないため定義していない。
///         必要に応じて定義する。
///
#ifndef INCLUDED_EGEG_WINDOW_HEADER_
#define INCLUDED_EGEG_WINDOW_HEADER_

#include <type_traits>
#include <memory>
#include <vector>
#include <functional>
#include <Windows.h>

namespace easy_engine {

class EasyEngine;

///
/// \class  WindowManager
/// \brief  ウィンドウマネージャー
///
///         このクラスへのアクセスは、EasyEngine::window()を使用してください。
///
class WindowManager {
public :
    friend EasyEngine;

    ///
    /// \brief  ウィンドウハンドルを取得
    ///
    /// \return ウィンドウハンドル
    ///
    HWND handle() const noexcept { return handle_; }
    
    ///
    /// \brief  コールバック関数を追加
    ///
    ///         クラスのメンバ関数用です。
    ///         ウィンドウイベントが発生したときに呼び出される関数を追加します。
    ///
    /// \tparam OwnerTy : 追加する関数のオーナー型
    /// \param[in] Owner : 追加する関数のオーナー
    /// \param[in] Callback : 追加する関数
    ///
    template <class OwnerTy>
    void addCallback(OwnerTy* Owner, void(OwnerTy::*Callback)(HWND, UINT, WPARAM, LPARAM)) {
        using namespace std::placeholders;
        addCallback(std::bind(Callback, Owner, _1, _2, _3, _4));
    }
    ///
    /// \brief  コールバック関数を追加
    ///
    ///         ウィンドウイベントが発生したときに呼び出される関数を追加します。
    ///
    /// \tparam FTy : 追加する関数型
    /// \param[in] Callback : 追加する関数
    ///
    template <class FTy>
    void addCallback(FTy&& Callback) {
        callbacks_.emplace_back(std::forward<FTy>(Callback));
    }
private :
    static std::unique_ptr<WindowManager> create();
    WindowManager();

    HWND handle_;
    std::vector<std::function<void(HWND, UINT, WPARAM, LPARAM)>>& callbacks_;
};

} // namespace easy_engine
#endif // !INCLUDED_EGEG_WINDOW_HEADER_
// EOF
