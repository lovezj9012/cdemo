/*
* ��飺����Boost����http��Post/Get����
* ���ߣ���³��
* ���䣺727057301@qq.com
* CSDN��http://blog.csdn.net/csnd_ayo
* ���ƣ�https://git.oschina.net/Mr_ChenLuYong
* github��http://github.com/chenluyong
* ����ʱ�䣺2017��3��12�� 04:32:07
* VS�汾��VS2013
* Boost�汾��boost_1_61_0
*/

#ifndef __CLY_HTTPBOOST_H__
#define __CLY_HTTPBOOST_H__

#include "HttpBase.h"

#include <boost/asio.hpp>



class HttpBoost :
	public HttpBase {

public:

	HttpBoost(boost::asio::io_service& io_service/*,FILE* dbg*/);

	virtual ~HttpBoost();

	/*
	* ����Post����
	*/
	virtual int post(const std::string& url, const std::string& authentication);

	/*
	* ����get����
	*/
	virtual int get(const std::string& url, const std::string& authentication);

	virtual std::string getResponse(void) {
		boost::system::error_code ignored_ec;  
		socket_.close(ignored_ec);// �ر�socket  
		return responseData_;
	}
	
private:
	// ��������
	void handle_request_resolve(const std::string& url,const std::string& authentication, pBuildRequest func);

	// ������
	void handle_resolve(const boost::system::error_code& err,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	// ���Ӻ�
	void handle_connect(const boost::system::error_code& err);

	// ���������
	void handle_write_request(const boost::system::error_code& err);
	
	// ��ȡ��Ӧ��
	void handle_read_status_line(const boost::system::error_code& err);
	
	// ��ȡ��Ӧͷ��
	void handle_read_headers(const boost::system::error_code& err);

	// ��ȡ�������ݺ�
	void handle_read_content(const boost::system::error_code& err);
private:

	// ������
	boost::asio::ip::tcp::resolver resolver_;
	// �׽���
	boost::asio::ip::tcp::socket socket_;
	// ���󻺳���
	boost::asio::streambuf *request_;
	// ��Ӧ������
	boost::asio::streambuf *response_;
	// ��Ӧ����
	std::string responseData_;
private:
	FILE* dbgf;

};

std::string post(std::string url,std::string authentication);



std::string get(std::string url, std::string& authentication);



#endif // __CLY_HTTPBOOST_H__