#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include <Windows.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
//#include <boost/json.hpp>


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
	char szSrcBuffer[1024] = { "[{\"couponNo\": \"0\",\"dateOfIssue\" : 1675699200000,\"mchRelatedCode\" : \"1072821274415747073\",\"prefix\" : \"999\",\"salesType\" : \"E\",\"ticketNo\" : \"2436163381\",\"ticketType\" : \"P\",\"traceCode\" : \"1125430417315450880\",\"transactionSeq\" : \"1072820137981915140\"}]" };
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

struct person {
	string name;
	int age;
};

struct resultVo {
	int code;
	string message;
	person p[10];
};


//读取json文件{"code":200,"message":"success","data":{"name":"zhangsan","age":25}}
template<class T>
void readJson(const string& data, T& t) {
	std::size_t start = data.find_first_of("{");
	std::size_t end = data.find_last_of("}");
	string res = data.substr(start, end-start+1);
	//string res = "{\"code\":200,\"message\":\"success\",\"data\":{\"name\":\"zhangsan\",\"age\":25}}";
	std::stringstream ss(res);
	boost::property_tree::ptree pt;
	//boost::property_tree::read_json(ss, pt);
	boost::property_tree::json_parser::read_json(ss, pt);
	//auto v = boost::json::parse(res);
	auto result = pt.get<T>("beforeAfterTimeDifference");
	//std::cout << "json:" << result << std::endl;
}


void postCustom(const string& url, const string& token) {
	boost::asio::io_service io;
	HttpBoost c(io);
	c.post(url, token);
	io.run();
	string p;
	readJson(c.getResponse(),p);
	std::cout << c.getResponse() << endl;
}

string parseJson(const boost::property_tree::ptree& tree) {

	std::ostringstream buf;
	boost::property_tree::write_json(buf, tree, false);
	return buf.str();
}


int main() {

	//设置编码格式
	SetConsoleOutputCP(65001);

	//unsigned short us = 65538;
	//cout <<"us=" << us << endl;

	//short sh = 32769;
	//cout <<"sh=" << sh << endl;

	//return 0;




	//HttpPost();

	//HttpBoost();
	//boost::property_tree::ptree tree;
	//tree.put("name", "jack");
	//tree.put("age", 30);
	//tree.put("address", "BeiJing");
	//tree.put("sex", true);
	//parseJson(tree);

	//custome
	/*string url = "http://localhost:8001/eduservice/chapter/addChapter/[{\"courseId\":\"1639144627057586178\",\"title\" : \"4\",\"sort\" : 0}]";
	string token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJzY2hvb2wtdXNlciIsImlhdCI6MTY5MDE2MzYzOSwiZXhwIjoxNjkwMjUwMDM5LCJpZCI6IjE2MzU0Njk5MDU1NzI3MDQyNTgiLCJuaWNrbmFtZSI6IjEyMyJ9.ZK85giE-wP-UL41wNxz8rqupEDGCn1afidvW7YfJB3g";*/

	/*//adm test
	boost::property_tree::ptree admtree;
	admtree.put("prefix", "999");
	admtree.put("memoType", "ADM");
	admtree.put("admOrderNo", "9996020000284");
	admtree.put("tktRelation", "Y");

	string json="["+ parseJson(admtree);
	json.append(",");
	json = json.substr(0, json.length() - 1);
	json.append("]");
	//string url = "https://test/uploadAdm[[{\"prefix\":\"999\",\"formType\":\"\",\"memoType\":\"ADM\",\"serialNo\":\"9996020000284\",\"admOrderNo\":\"9996020000284\",\"tktRelation\":\"Y\",\"agentNo\":\"08322705\",\"agentName\":\"阿斯兰航空服务（上海）有限公司\",\"status\":\"Y\",\"station\":\"BJS\",\"admCreateDate\":\"20230717\",\"reviewUser\":\"mas\",\"reviewDate\":\"20230801\",\"admReviewDate\":\"20230801\"}]]";
	string url = "https://test/uploadAdm[";
	url = url + json + "]";
	string token = "ZBHS2H5iRok2tSDptbIGdUZJS63ohkH3";
	postCustom(url, token);*/

	//string url = "https://test[{\"validatingCarrier\":\"CA\",   \"oldValidatingCarrier\":\"CA\",   \"diInd\":\"I\",   \"salesType\":\"E\",   \"passengerType\":\"ADT\",   \"refOrExgAgentNo\":\"08366666\",   \"agentNo\":\"08366666\",   \"refOrExgDateOfIssue\":\"20220530\",   \"dateOfIssue\":\"20220530\",   \"originCityCode\":\"BJS\",   \"originAirportCode\":\"BJS\",   \"destinationCityCode\":\"SHA\",   \"destinationAirportCode\":\"SHA\",   \"flightDate\":\"20230118\",   \"carrier\":\"CA\",   \"operatingCarrier\":\"CA\",   \"cabinClass\":\"C\",   \"rbd\":\"C\",   \"fareBasis\":\"C\",   \"beforeAfterInd\":\"B\",   \"beforeAfterTimeDifference\":20.666 }]";
	string url = "http://test[{\"validatingCarrier\":\"CA\",   \"oldValidatingCarrier\":\"CA\",   \"diInd\":\"I\",   \"salesType\":\"E\",   \"passengerType\":\"ADT\",   \"refOrExgAgentNo\":\"08366666\",   \"agentNo\":\"08366666\",   \"refOrExgDateOfIssue\":\"20220530\",   \"dateOfIssue\":\"20220530\",   \"originCityCode\":\"BJS\",   \"originAirportCode\":\"BJS\",   \"destinationCityCode\":\"SHA\",   \"destinationAirportCode\":\"SHA\",   \"flightDate\":\"20230118\",   \"carrier\":\"CA\",   \"operatingCarrier\":\"CA\",   \"cabinClass\":\"C\",   \"rbd\":\"C\",   \"fareBasis\":\"C\",   \"beforeAfterInd\":\"B\",   \"beforeAfterTimeDifference\":20.666 }]";
	
	postCustom(url, "");
	

	return 0;
}