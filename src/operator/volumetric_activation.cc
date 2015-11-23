/*!
 * Copyright (c) 2015 by Contributors
 * \file activation.cc
 * \brief activation op
 * \author Bing Xu
*/
#include "./volumetric_activation-inl.h"
#include "./mshadow_op.h"

namespace mxnet {
namespace op {
template<>
Operator *CreateOp<cpu>(VolumetricActivationParam param) {
  switch (param.act_type) {
    case activation::kReLU:
      return new VolumetricActivationOp<cpu, mshadow_op::relu, mshadow_op::relu_grad>();
    case activation::kSigmoid:
      return new VolumetricActivationOp<cpu, mshadow_op::sigmoid, mshadow_op::sigmoid_grad>();
    case activation::kTanh:
      return new VolumetricActivationOp<cpu, mshadow_op::tanh, mshadow_op::tanh_grad>();
    default:
      LOG(FATAL) << "unknown activation type";
      return NULL;
  }
}

// DO_BIND_DISPATCH comes from operator_common.h
Operator *VolumetricActivationProp::CreateOperator(Context ctx) const {
  DO_BIND_DISPATCH(CreateOp, param_);
}

DMLC_REGISTER_PARAMETER(VolumetricActivationParam);

MXNET_REGISTER_OP_PROPERTY(VolumetricActivation, VolumetricActivationProp)
.describe("Apply volumetric activation function to input.")
.add_argument("data", "Symbol", "Input data to activation function.")
.add_arguments(VolumetricActivationParam::__FIELDS__());

}  // namespace op
}  // namespace mxnet
