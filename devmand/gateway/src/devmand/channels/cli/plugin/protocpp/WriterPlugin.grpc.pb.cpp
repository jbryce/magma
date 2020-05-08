// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: WriterPlugin.proto

#include "WriterPlugin.grpc.pb.h"
#include "WriterPlugin.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace devmand {
namespace channels {
namespace cli {
namespace plugin {

static const char* WriterPlugin_method_names[] = {
    "/devmand.channels.cli.plugin.WriterPlugin/Create",
    "/devmand.channels.cli.plugin.WriterPlugin/Update",
    "/devmand.channels.cli.plugin.WriterPlugin/Remove",
};

std::unique_ptr<WriterPlugin::Stub> WriterPlugin::NewStub(
    const std::shared_ptr<::grpc::ChannelInterface>& channel,
    const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr<WriterPlugin::Stub> stub(new WriterPlugin::Stub(channel));
  return stub;
}

WriterPlugin::Stub::Stub(
    const std::shared_ptr<::grpc::ChannelInterface>& channel)
    : channel_(channel),
      rpcmethod_Create_(
          WriterPlugin_method_names[0],
          ::grpc::RpcMethod::BIDI_STREAMING,
          channel),
      rpcmethod_Update_(
          WriterPlugin_method_names[1],
          ::grpc::RpcMethod::BIDI_STREAMING,
          channel),
      rpcmethod_Remove_(
          WriterPlugin_method_names[2],
          ::grpc::RpcMethod::BIDI_STREAMING,
          channel) {}

::grpc::ClientReaderWriter<
    ::devmand::channels::cli::plugin::CreateRequest,
    ::devmand::channels::cli::plugin::CreateResponse>*
WriterPlugin::Stub::CreateRaw(::grpc::ClientContext* context) {
  return new ::grpc::ClientReaderWriter<
      ::devmand::channels::cli::plugin::CreateRequest,
      ::devmand::channels::cli::plugin::CreateResponse>(
      channel_.get(), rpcmethod_Create_, context);
}

::grpc::ClientAsyncReaderWriter<
    ::devmand::channels::cli::plugin::CreateRequest,
    ::devmand::channels::cli::plugin::CreateResponse>*
WriterPlugin::Stub::AsyncCreateRaw(
    ::grpc::ClientContext* context,
    ::grpc::CompletionQueue* cq,
    void* tag) {
  return new ::grpc::ClientAsyncReaderWriter<
      ::devmand::channels::cli::plugin::CreateRequest,
      ::devmand::channels::cli::plugin::CreateResponse>(
      channel_.get(), cq, rpcmethod_Create_, context, tag);
}

::grpc::ClientReaderWriter<
    ::devmand::channels::cli::plugin::UpdateRequest,
    ::devmand::channels::cli::plugin::UpdateResponse>*
WriterPlugin::Stub::UpdateRaw(::grpc::ClientContext* context) {
  return new ::grpc::ClientReaderWriter<
      ::devmand::channels::cli::plugin::UpdateRequest,
      ::devmand::channels::cli::plugin::UpdateResponse>(
      channel_.get(), rpcmethod_Update_, context);
}

::grpc::ClientAsyncReaderWriter<
    ::devmand::channels::cli::plugin::UpdateRequest,
    ::devmand::channels::cli::plugin::UpdateResponse>*
WriterPlugin::Stub::AsyncUpdateRaw(
    ::grpc::ClientContext* context,
    ::grpc::CompletionQueue* cq,
    void* tag) {
  return new ::grpc::ClientAsyncReaderWriter<
      ::devmand::channels::cli::plugin::UpdateRequest,
      ::devmand::channels::cli::plugin::UpdateResponse>(
      channel_.get(), cq, rpcmethod_Update_, context, tag);
}

::grpc::ClientReaderWriter<
    ::devmand::channels::cli::plugin::RemoveRequest,
    ::devmand::channels::cli::plugin::RemoveResponse>*
WriterPlugin::Stub::RemoveRaw(::grpc::ClientContext* context) {
  return new ::grpc::ClientReaderWriter<
      ::devmand::channels::cli::plugin::RemoveRequest,
      ::devmand::channels::cli::plugin::RemoveResponse>(
      channel_.get(), rpcmethod_Remove_, context);
}

::grpc::ClientAsyncReaderWriter<
    ::devmand::channels::cli::plugin::RemoveRequest,
    ::devmand::channels::cli::plugin::RemoveResponse>*
WriterPlugin::Stub::AsyncRemoveRaw(
    ::grpc::ClientContext* context,
    ::grpc::CompletionQueue* cq,
    void* tag) {
  return new ::grpc::ClientAsyncReaderWriter<
      ::devmand::channels::cli::plugin::RemoveRequest,
      ::devmand::channels::cli::plugin::RemoveResponse>(
      channel_.get(), cq, rpcmethod_Remove_, context, tag);
}

WriterPlugin::Service::Service() {
  (void)WriterPlugin_method_names;
  AddMethod(new ::grpc::RpcServiceMethod(
      WriterPlugin_method_names[0],
      ::grpc::RpcMethod::BIDI_STREAMING,
      new ::grpc::BidiStreamingHandler<
          WriterPlugin::Service,
          ::devmand::channels::cli::plugin::CreateRequest,
          ::devmand::channels::cli::plugin::CreateResponse>(
          std::mem_fn(&WriterPlugin::Service::Create), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      WriterPlugin_method_names[1],
      ::grpc::RpcMethod::BIDI_STREAMING,
      new ::grpc::BidiStreamingHandler<
          WriterPlugin::Service,
          ::devmand::channels::cli::plugin::UpdateRequest,
          ::devmand::channels::cli::plugin::UpdateResponse>(
          std::mem_fn(&WriterPlugin::Service::Update), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      WriterPlugin_method_names[2],
      ::grpc::RpcMethod::BIDI_STREAMING,
      new ::grpc::BidiStreamingHandler<
          WriterPlugin::Service,
          ::devmand::channels::cli::plugin::RemoveRequest,
          ::devmand::channels::cli::plugin::RemoveResponse>(
          std::mem_fn(&WriterPlugin::Service::Remove), this)));
}

WriterPlugin::Service::~Service() {}

::grpc::Status WriterPlugin::Service::Create(
    ::grpc::ServerContext* context,
    ::grpc::ServerReaderWriter<
        ::devmand::channels::cli::plugin::CreateResponse,
        ::devmand::channels::cli::plugin::CreateRequest>* stream) {
  (void)context;
  (void)stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status WriterPlugin::Service::Update(
    ::grpc::ServerContext* context,
    ::grpc::ServerReaderWriter<
        ::devmand::channels::cli::plugin::UpdateResponse,
        ::devmand::channels::cli::plugin::UpdateRequest>* stream) {
  (void)context;
  (void)stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status WriterPlugin::Service::Remove(
    ::grpc::ServerContext* context,
    ::grpc::ServerReaderWriter<
        ::devmand::channels::cli::plugin::RemoveResponse,
        ::devmand::channels::cli::plugin::RemoveRequest>* stream) {
  (void)context;
  (void)stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

} // namespace plugin
} // namespace cli
} // namespace channels
} // namespace devmand