#include <iostream>
#include <grpcpp/grpcpp.h>
#include <string>
#include <memory>
//#include <grpcpp/health_check_service_interface.h>
//#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "demo.grpc.pb.h"
#include "demo.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;
using namespace  std;


class GreeterServiceImpl : public Greeter::Service {
	Status SayHello(ServerContext *context, const HelloRequest *request, HelloReply *response) override {
		string prefix("Hello, ");
		response->set_message(prefix + request->name());
		return Status::OK;
	}
};

void RunServer();
int main()
{
	std::cout << "Hello, World!" << std::endl;
	RunServer();
	return 0;
}
void RunServer()
{
	string address("0.0.0.0:34001");
	GreeterServiceImpl service;
	ServerBuilder serverBuilder;
	serverBuilder.AddListeningPort(address, grpc::InsecureServerCredentials());
	serverBuilder.RegisterService(&service);
	unique_ptr<Server> server(serverBuilder.BuildAndStart());
	cout << "Server listening on " << address << endl;
	server->Wait();
}
