// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: examples.proto

#include "examples.pb.h"
#include "examples.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>

static const char* SearchService_method_names[] = {
  "/SearchService/Search",
};

std::unique_ptr< SearchService::Stub> SearchService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< SearchService::Stub> stub(new SearchService::Stub(channel));
  return stub;
}

SearchService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Search_(SearchService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status SearchService::Stub::Search(::grpc::ClientContext* context, const ::SearchRequest& request, ::SearchResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Search_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::SearchResponse>* SearchService::Stub::AsyncSearchRaw(::grpc::ClientContext* context, const ::SearchRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::SearchResponse>::Create(channel_.get(), cq, rpcmethod_Search_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::SearchResponse>* SearchService::Stub::PrepareAsyncSearchRaw(::grpc::ClientContext* context, const ::SearchRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::SearchResponse>::Create(channel_.get(), cq, rpcmethod_Search_, context, request, false);
}

SearchService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SearchService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< SearchService::Service, ::SearchRequest, ::SearchResponse>(
          std::mem_fn(&SearchService::Service::Search), this)));
}

SearchService::Service::~Service() {
}

::grpc::Status SearchService::Service::Search(::grpc::ServerContext* context, const ::SearchRequest* request, ::SearchResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


