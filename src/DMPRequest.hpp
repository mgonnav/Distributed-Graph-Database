// Copyright 2021 <The Three Musketeers UCSP>
#ifndef SRC_DMPREQUEST_HPP_
#define SRC_DMPREQUEST_HPP_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <list>
#include <memory>
#include <vector>

namespace DMP {

enum RequestType {
  kCreateRequest,
  kReadRequest,
  kUpdateRequest,
  kDeleteRequest
};

struct ClientRequest {
  char accion;

  ClientRequest(char action, RequestType type) : accion(action), _type(type) {}

  virtual ~ClientRequest() {}

  RequestType type() const {
    return _type;
  }

  virtual void PrintStructure() const {}
  virtual char* ParseToCharBuffer() const {
    return nullptr;
  }

 private:
  RequestType _type;
};

struct CreateRequest : ClientRequest {
  int action;
  int name_node_size;
  char name_node[255];
  int number_of_attributes;
  int number_of_relations;

  CreateRequest() : ClientRequest('C', kCreateRequest) {}
  ~CreateRequest() {}

  void PrintStructure() const override;
  char* ParseToCharBuffer() const override;
};

struct ReadRequest : ClientRequest {
  int action;
  int query_node_size;
  char query_node[99];
  int deep;
  int leaf;
  int attributes;
  int number_of_conditions;

  ReadRequest() : ClientRequest('R', kReadRequest) {}
  ~ReadRequest() {}

  void PrintStructure() const override;
  char* ParseToCharBuffer() const override;
};

struct UpdateRequest : ClientRequest {
  int action;
  int node_or_attribute;
  int  query_node_size;
  char query_value_node[99];

  UpdateRequest() : ClientRequest('U', kUpdateRequest) {}
  ~UpdateRequest() {}

  void PrintStructure() const override;
  char* ParseToCharBuffer() const override;
};

struct DeleteRequest : ClientRequest {
  int action;
  int node_or_attribute;
  int  query_node_size;
  char query_value_node[99];

  DeleteRequest() : ClientRequest('D', kDeleteRequest) {}
  ~DeleteRequest() {}

  void PrintStructure() const override;
  char* ParseToCharBuffer() const override;
};

std::shared_ptr<ClientRequest> ProcessRequest(int connectionFD);

}  // namespace DMP

#endif  // SRC_DMPREQUEST_HPP_
