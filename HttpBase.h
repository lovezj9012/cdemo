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

#ifndef __CLY_HTTPBASE_H__
#define __CLY_HTTPBASE_H__

#include <iostream>

using namespace std;


class HttpBase {

public:

	HttpBase();

	virtual ~HttpBase();

	/*
	* ����Post����
	*/
	virtual int post(const std::string& url,const std::string& authentication) = 0;

	/*
	* ����get����
	*/
	virtual int get(const std::string& url,const std::string& authentication) = 0;

	virtual std::string getResponse(void) = 0;

protected:
	typedef int(*pBuildRequest)(const string&, const string&,
		std::ostream&,const std::string&);

	/*
	* ����URL
	* parseUrl
	* url: ��������URL
	* out_server: ��������
	* out_port: �˿ں�
	* out_path: ��������ҳ
	*/
	static int parseUrl(const std::string& url, std::string& out_server,
		std::string& out_port, std::string& out_path);

	/*
	* ����Post����
	* buildPostRequest
	*/
	static int buildPostRequest(const std::string& server, const std::string& path,
					std::ostream& out_request,const std::string& authentication);

	/*
	* ����Get����
	* buildGetRequest
	*/
	static int buildGetRequest(const std::string& server, const std::string& path,
					std::ostream& out_request, const std::string& authentication);

};



#endif // __CLY_HTTPBASE_H__
