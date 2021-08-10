#include "connection_metadata.h"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;


    typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

    connection_metadata::connection_metadata(int id, websocketpp::connection_hdl hdl, std::string uri)
      : m_id(id)
      , m_hdl(hdl)
      , m_status("Connecting")
      , m_uri(uri)
      , m_server("N/A")

    {  }

    void connection_metadata::on_open(client * c, std::string text, websocketpp::connection_hdl hdl) {
        m_status = "Open";
        //std::cout << "text:" << text << std::endl;
        client::connection_ptr con = c->get_con_from_hdl(hdl);
        m_server = con->get_response_header("Server");

        std::string payload = text;
        c->send(hdl, payload, websocketpp::frame::opcode::text);

    }

    void connection_metadata::on_fail(client * c, websocketpp::connection_hdl hdl) {
        m_status = "Failed";

        client::connection_ptr con = c->get_con_from_hdl(hdl);
        m_server = con->get_response_header("Server");
        m_error_reason = con->get_ec().message();
    }

    void connection_metadata::on_close(client * c, websocketpp::connection_hdl hdl) {
        m_status = "Closed";
        client::connection_ptr con = c->get_con_from_hdl(hdl);
        std::stringstream s;
        s << "close code: " << con->get_remote_close_code() << " ("
          << websocketpp::close::status::get_string(con->get_remote_close_code())
          << "), close reason: " << con->get_remote_close_reason();
        m_error_reason = s.str();
    }

    void connection_metadata::on_message(client * c, std::string* ret_msg, websocketpp::connection_hdl hdl, client::message_ptr msg) {
        if (msg->get_opcode() == websocketpp::frame::opcode::text) {
            m_messages.push_back("<< " + msg->get_payload());
        } else {
            m_messages.push_back("<< " + websocketpp::utility::to_hex(msg->get_payload()));
        }
        *ret_msg = msg->get_payload();
        std::cout << "msgpayload: " << *ret_msg << std::endl;
        c->close(hdl, websocketpp::close::status::normal, "finished receiving message");


    }

    websocketpp::connection_hdl connection_metadata::get_hdl() const {
        return m_hdl;
    }

    int connection_metadata::get_id() const {
        return m_id;
    }

    std::string connection_metadata::get_status() const {
        return m_status;
    }

    void connection_metadata::record_sent_message(std::string message) {
        m_messages.push_back(">> " + message);
    }

