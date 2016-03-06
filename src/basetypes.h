//
// Created by tkorays on 3/6/16.
//

#ifndef INVOKER_BASETYPES_H
#define INVOKER_BASETYPES_H

#include <stdint.h>

namespace inv {

#define TYPE_NAME_LENGTH 15
#define TYPE_NAME_SIZE   (TYPE_NAME_LENGTH+1)

    typedef enum {
        type_char=0,
        type_int8=0,
        type_uchar=1,
        type_uint8=1,
        type_int16,
        type_uint16,
        type_int32,
        type_uint32,
        type_int64,
        type_uint64,
        type_bit1,
        type_bit2,
        type_bit3,
        type_bit4,
        type_bit5,
        type_bit6,
        type_bit7,
        type_user
    } base_type_id;

    /// @brief 基本数据类型定义
    class base_type {
    public:
        base_type_id      id;                      ///< 类型id
        char              name[TYPE_NAME_SIZE];    ///< 类型名称
        uint8_t           bits;                    ///< 类型占用位数
        uint8_t           bytes;                   ///< 实际占用字节
    };

    


};

#endif //INVOKER_BASETYPES_H
