#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include <Windows.h>

#include "HttpBoost.h"

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

unsigned char ToHex(unsigned char x)
{
	return  x > 9 ? x + 55 : x + 48;
}


unsigned char FromHex(unsigned char x)
{
	unsigned char y;

	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else assert(0);
	return y;
}


std::string UrlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~') ||
			(str[i] == '&') ||
			(str[i] == '='))
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] % 16);
		}
	}
	return strTemp;
}


std::string UrlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '+') strTemp += ' ';
		else if (str[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high * 16 + low;
		}
		else strTemp += str[i];
	}
	return strTemp;
}




int HttpPost()
{
	//	char szSrcBuffer[1024] = { "authorJson={loginAccount:\"admin\"}&parmJson={code:\"SheBeiLiXianGaoJingShangChuan\",params:{id:\"123456\",remarks:\"fire alarm\",time_alarm:\"2017-1-1\",alarm_source:\"192.168.1.11\"}}" };
	//char szSrcBuffer[1024] = { "authorJson={loginAccount:\"admin\"}&parmJson={code:\"SheBeiLiXianChaXun\",params:{}}" };
	char szSrcBuffer[1024] = {"[{\"couponNo\": \"0\",\"dateOfIssue\" : 1675699200000,\"mchRelatedCode\" : \"1072821274415747073\",\"prefix\" : \"999\",\"salesType\" : \"E\",\"ticketNo\" : \"2436163381\",\"ticketType\" : \"P\",\"traceCode\" : \"1125430417315450880\",\"transactionSeq\" : \"1072820137981915140\"}]"};
	std::string strUrlEnCodedBuffer = UrlEncode(szSrcBuffer);
	io_service iosev;
	ip::tcp::socket socket(iosev);
	ip::tcp::endpoint ep(ip::address_v4::from_string("10.1.18.183"), 28080);
	boost::system::error_code ec;
	socket.connect(ep, ec);
	if (ec) return -1;
	boost::asio::streambuf request;
	std::ostream request_stream(&request);
	request_stream << "POST /sams-ca/sat/validateRetireTkt HTTP/1.1\r\n";
	request_stream << "Host: 10.1.18.183:28080\r\n";
	//request_stream << "Connection: keep-alive\r\n";
	request_stream << "Content-Length: " << strUrlEnCodedBuffer.size() << "\r\n";
	request_stream << "Content-Type: application/json; charset=UTF-8\r\n";
	//request_stream << "User-Agent: Mozilla/4.0\r\n";
	//request_stream << "Accept-Language: zh-CN\r\n\r\n";
	request_stream << "Accept: application/json\r\n";
	request_stream << "\r\n";
	request_stream << strUrlEnCodedBuffer;

	size_t len = boost::asio::write(socket, request);

	char szRecvBuf[1024] = { 0 };
	socket.read_some(buffer(szRecvBuf), ec);
	std::cout << "Http Response Context:" << std::endl;
	std::cout << szRecvBuf << std::endl;
	std::string strRecvBuf = szRecvBuf;
	int nIndexOfBody = strRecvBuf.find("\r\n\r\n", 0);
	if (nIndexOfBody < 0) return -1;

	std::string strHttpBody = strRecvBuf.substr(nIndexOfBody + 4);
	std::cout << "Http Body Context:" << std::endl;
	std::cout << strHttpBody << std::endl;
	return 0;

}


//int HttpBoost() {
//
//		try
//		{
//			boost::asio::io_service io_service;
//
//			//获取URL信息和协议类型
//			tcp::resolver resolver(io_service);
//			tcp::resolver::query query("127.0.0.1", "8080");
//			tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
//
//			//连接到服务器
//			tcp::socket socket(io_service);
//			boost::asio::connect(socket, endpoint_iterator);
//
//			//构造HTTP请求消息
//			boost::asio::streambuf request;
//			std::ostream request_stream(&request);
//			request_stream << "POST /sams-ca/sat/validateRetireTkt HTTP/1.0\r\n";
//			request_stream << "Host: 127.0.0.1:8080\r\n";
//			request_stream << "Content-Type:application/json\r\n";
//			request_stream << "Accept: */*\r\n";
//			request_stream << "Connection: close\r\n\r\n";
//
//			//发送HTTP请求消息
//			boost::asio::write(socket, request);
//
//			//读取HTTP响应消息
//			boost::asio::streambuf response;
//			boost::asio::read_until(socket, response, "\r\n");
//
//			//检查响应是否正常
//			std::istream response_stream(&response);
//			std::string http_version;
//			response_stream >> http_version;
//			unsigned int status_code;
//			response_stream >> status_code;
//			std::string status_message;
//			std::getline(response_stream, status_message);
//
//			if (!response_stream || http_version.substr(0, 5) != "HTTP/")
//			{
//				std::cout << "无效响应\n";
//				return 1;
//			}
//
//			if (status_code != 200)
//			{
//				std::cout << "请求错误, 状态码： " << status_code << "\n";
//				return 1;
//			}
//
//			//处理 HTTP 响应消息体
//			boost::asio::read_until(socket, response, "\r\n\r\n");
//
//			//找到Content-Length
//			std::string header;
//			while (std::getline(response_stream, header) && header != "\r")
//			{
//				if (header.find("Content-Length: ") == 0)
//				{
//					long long content_length = std::stoll(header.substr(16));
//					std::cout << "文件大小为: " << content_length << " bytes.\n";
//
//					//读取文件内容并写入本地文件
//					std::ofstream output_file("example.html", std::ios::binary);
//					if (!output_file)
//					{
//						std::cout << "无法创建文件！\n";
//						return 1;
//					}
//					std::vector<char> buffer(1024 * 1024); //使用1MB缓冲区
//					long long bytes_read = 0;
//					while (bytes_read < content_length)
//					{
//						long long read_length = std::min((long long)buffer.size(), content_length - bytes_read);
//						boost::asio::read(socket, boost::asio::buffer(buffer.data(), read_length));
//						output_file.write(buffer.data(), read_length);
//						bytes_read += read_length;
//					}
//					std::cout << "文件下载完成！\n";
//					break;
//				}
//			}
//		}
//		catch (std::exception& e)
//		{
//			std::cout << "下载错误: " << e.what() << "\n";
//			return 1;
//		}
//
//		return 0;
//}
//

int main() {
	//设置编码格式
	SetConsoleOutputCP(65001);
	//HttpPost();

	//HttpBoost();

	string url = "http://localhost:8001/eduservice/chapter/addChapter/[{\"courseId\":\"1639144627057586178\",\"title\" : \"4\",\"sort\" : 0}]";
	
	//string url = "https://www.kuaidi100.com/query/[{\"type\":\"yuantong\",\"postid\":\"11111111111\"}]";


	boost::asio::io_service io;
	HttpBoost c(io);
	c.post(url,"");
	io.run();
	std::cout << c.getResponse() << endl;

	return 0;
}