///
/// \file   update_order.hpp
/// \brief  �X�V������`�w�b�_
///
///         �X�V�}�l�[�W���[�ɍX�V������o�^����ۂ́A
///         �D�揇�ʎw��Ɏg�p���܂��B
///         �K�v�ɍ��킹�ĕύX�������Ă��������B
///
/// \attention kUpdateBegin
///            kUpdateEnd
///            kRenderBegin
///            kRenderEnd �ɂ��āA\n
///            �X�V�����o�^���Ɏg�p���邱�Ƃ͖�肠��܂��񂪁A
///            �ʒu�֌W�̕ύX�A���l�̑�����X�A�ύX�������Ă͂����܂���B
///
#ifndef INCLUDED_EGEG_UPDATE_ORDER_HEADER_
#define INCLUDED_EGEG_UPDATE_ORDER_HEADER_

namespace easy_engine {
enum UpdateOrder {
    kUpdateBegin = 5,
// ������ ���R�ɒǉ��A�폜���Ă� ������



// ������ ���R�ɒǉ��A�폜���Ă� ������
    kUpdateEnd,
///////////////////////////////////////////////
    kRenderBegin,
// ������ ���R�ɒǉ��A�폜���Ă� ������



// ������ ���R�ɒǉ��A�폜���Ă� ������
    kRenderEnd,
};
}
#endif // !INCLUDED_EGEG_UPDATE_ORDER_HEADER_
// EOF
