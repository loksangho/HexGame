#pragma once

#ifndef WEBSOCKET_ENDPOINT_H
#define WEBSOCKET_ENDPOINT_H

#include "connection_metadata.h"

class websocket_endpoint {
public:
    websocket_endpoint ();

    ~websocket_endpoint();

    int connect(std::string const & uri, std::string text, std::string sessionid, std::string csrftoken, std::string* ret_msg);

    void close(int id, websocketpp::close::status::value code, std::string reason);

    void send(int id, std::string message);

    connection_metadata::ptr get_metadata(int id) const;
private:
    typedef std::map<int,connection_metadata::ptr> con_list;

    client m_endpoint;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;
    std::string m_text;
    con_list m_connection_list;
    int m_next_id;
};

#endif // WEBSOCKET_ENDPOINT_H
