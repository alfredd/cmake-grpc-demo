//
// Created by alfredd on 10/24/20.
//

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "demo.grpc.pb.h"
#include "demo.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;


class GreeterClient {
public:
	GreeterClient(std::shared_ptr<Channel> channel) : stub_(Greeter::NewStub(channel)) {}

	std::string SayHello(const std::string& user) {
		HelloRequest request;
		request.set_name(user);

		HelloReply reply;

		ClientContext context;

		Status status = stub_->SayHello(&context, request, &reply);
		if (status.ok()) {
			return reply.message();
		} else {
			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
			return "RPC failed";
		}
	}

private:
	std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
	std::string server("localhost:34001");
	GreeterClient client(grpc::CreateChannel(server, grpc::InsecureChannelCredentials()));
	std::string user("World");
	std::string reply = client.SayHello(user);
	std::cout << "Response from server: " << reply << std::endl;

	return 0;
}