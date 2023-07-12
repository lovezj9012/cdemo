#include "HttpBoost.h"
#include <boost/bind.hpp>

#include "http_mark.h"
#include <boost/format.hpp>
HttpBoost::HttpBoost(boost::asio::io_service& io_service/*,FILE* dbg*/)
: resolver_(io_service), socket_(io_service)/*,dbgf(dbg)*/ {
}


HttpBoost::~HttpBoost() {

}


int HttpBoost::post(const std::string& url, const std::string& authentication) {
	handle_request_resolve(url, authentication, HttpBase::buildPostRequest);
	return HTTP_SUCCESS;
}


int HttpBoost::get(const std::string& url,const std::string& authentication) {
	handle_request_resolve(url, authentication, HttpBase::buildGetRequest);
	return HTTP_SUCCESS;
}


void HttpBoost::handle_request_resolve(const std::string& url, const std::string& authentication, pBuildRequest func) {
	try {
		responseData_.clear();
		
		// ����URL
		std::string server, port, path;
		parseUrl(url, server, port, path);
		request_ = new boost::asio::streambuf;
		std::ostream request_stream(request_);

		// �ϳ�����
		func(server, path, request_stream,authentication);

		// ���������ַ\�˿�
		boost::asio::ip::tcp::resolver::query query(server, port);
		resolver_.async_resolve(query,
			boost::bind(&HttpBoost::handle_resolve, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::iterator));
	}
	catch (std::exception& e) {
		socket_.close();
		if (dbgf != NULL)
			fprintf(dbgf, "Exception: %s \n", e.what());
		else
		std::cout << "Exception: " << e.what() << "\n";
		throw;
	}	
	return;
}


void HttpBoost::handle_resolve(const boost::system::error_code& err,
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
	if (err) {
		if (dbgf != NULL)
			fprintf(dbgf, "Error: %s \n",err.message().c_str());
		else
		std::cout << "Error: " << err.message().c_str() << "\n";
		return;
	}
	socket_.async_connect(*endpoint_iterator,boost::bind(&HttpBoost::handle_connect, this,boost::asio::placeholders::error));
	// ��������
	/*boost::asio::async_connect(socket_, endpoint_iterator,
		boost::bind(&HttpBoost::handle_connect, this,
		boost::asio::placeholders::error));*/
}


void HttpBoost::handle_connect(const boost::system::error_code& err) {
	if (err) {
		if (dbgf != NULL)
			fprintf(dbgf, "Error: %s \n",err.message().c_str());
		else
			std::cout << "Error: " << err.message().c_str() << "\n";
		delete request_;
		return;
	}

	// ����request����
	boost::asio::async_write(socket_, *request_,
		boost::bind(&HttpBoost::handle_write_request, this,
		boost::asio::placeholders::error));
}


void HttpBoost::handle_write_request(const boost::system::error_code& err) {
	delete request_;
	if (err) {
		if (dbgf != NULL)
			fprintf(dbgf, "Error: %s \n",err.message().c_str());
		else
			std::cout << "Error: " << err.message().c_str() << "\n";
		return;
	}
	
	response_ = new boost::asio::streambuf;
	// �첽���������ݵ�*response_��ֱ������Э����� \r\n Ϊֹ
	boost::asio::async_read_until(socket_, *response_, "\r\n",
		boost::bind(&HttpBoost::handle_read_status_line, this,
		boost::asio::placeholders::error));
}


void HttpBoost::handle_read_status_line(const boost::system::error_code& err) {
	if (err) {
		if (dbgf != NULL)
			fprintf(dbgf, "Error: %s \n",err.message().c_str());
		else
			std::cout << "Error: " << err.message().c_str() << "\n";
		delete response_;
		response_=NULL;
		return;
	}

	// ����buff
	std::istream response_stream(response_);
	unsigned int status_code;
	std::string http_version, status_message;
	response_stream >> http_version;
	response_stream >> status_code;
	std::getline(response_stream, status_message);

	// �˶��Ƿ�����ȷ����
	if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
		if (dbgf != NULL)
			fprintf(dbgf, "�������Ӧ����\n");
		else			
			std::cout << "�������Ӧ����\n";
		return;
	}
	if (status_code != 200) {
		if (dbgf != NULL)
			fprintf(dbgf, "��������Ӧ��״̬��:%d \n",status_code);
		else	
		{
			//std::cout << "��������Ӧ��״̬��: " << status_code << "\n";
		}
		
		return;
	}

	// ��ȡ��Ӧͷ,ֱ������Э����� \r\n\r\n Ϊֹ
	boost::asio::async_read_until(socket_, *response_, "\r\n\r\n",
		boost::bind(&HttpBoost::handle_read_headers, this,
		boost::asio::placeholders::error));
}


void HttpBoost::handle_read_headers(const boost::system::error_code& err) {
	if (err) {
		if (dbgf != NULL)
			fprintf(dbgf, "Error: %s \n",err.message().c_str());
		else
			std::cout << "Error: " << err.message().c_str() << "\n";
		delete response_;
		response_=NULL;
		return;
	}
	// �����Ӧͷ
	std::istream response_stream(response_);
	std::string header;
	while (std::getline(response_stream, header) && header != "\r") {
#ifdef _DEBUG
		if (dbgf != NULL)
			fprintf(dbgf, "header: %s \n",header.c_str());
		else
			std::cout << header << "\n";
#endif 
	}
#ifdef _DEBUG
	//std::cout << "\n";
#endif 

	// д������ʣ�������
	if (response_->size() > 0) {
		boost::asio::streambuf::const_buffers_type cbt = response_->data();
		responseData_ += std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
//#ifdef _DEBUG
		//std::cout << *response_;
		std::stringstream stream;
		stream<<response_;
		
//#endif 
	}
	
	// ��ʼ��ȡʣ����������
	boost::asio::async_read(socket_, *response_,
		boost::asio::transfer_at_least(1),
		boost::bind(&HttpBoost::handle_read_content, this,
		boost::asio::placeholders::error));
}

void HttpBoost::handle_read_content(const boost::system::error_code& err) {
	if (!err) {
		// �������������
		boost::asio::streambuf::const_buffers_type cbt = response_->data();
		responseData_ += std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
#ifdef _DEBUG
		//std::cout << response_;
#endif 
		std::stringstream stream;
		stream<<response_;
		// ������ȡʣ�����ݣ�ֱ������EOF
		boost::asio::async_read(socket_, *response_,
			boost::asio::transfer_at_least(1),
			boost::bind(&HttpBoost::handle_read_content, this,
			boost::asio::placeholders::error));
	}
	else if (err != boost::asio::error::eof) {
		if (dbgf != NULL)
			fprintf(dbgf, "Error: %s \n",err.message().c_str());
		else
			std::cout << "Error: " << err.message().c_str() << "\n";
		//std::cout << "Error: " << err << "\n";
		delete response_;
		response_=NULL;
	}
	else {
		socket_.close();
		resolver_.cancel();	
		delete response_;
		response_=NULL;
		if (dbgf != NULL)
			fprintf(dbgf, "��ȡ��Ӧ�������");
		else
			;//std::cout << "��ȡ��Ӧ�������." << std::endl;
	}
}


//std::string post(std::string url) {
//	boost::asio::io_service io;
//	HttpBoost c(io);
//	c.post(url);
//	io.run();
//	return c.getResponse();
//}

/*std::string get(std::string url) {
	boost::asio::io_service io;
	HttpBoost c(io);
	c.get(url);
	io.run();
	return c.getResponse();
}*/