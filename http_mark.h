/*
* 简介：利用Boost发送http的Post/Get请求
* 作者：陈鲁勇
* 邮箱：727057301@qq.com
* CSDN：http://blog.csdn.net/csnd_ayo
* 码云：https://git.oschina.net/Mr_ChenLuYong
* github：http://github.com/chenluyong
* 创建时间：2017年3月12日 04:32:07
* VS版本：VS2013
* Boost版本：boost_1_61_0
*/  

#ifndef __CLY_HTTP_MARK_H__
#define __CLY_HTTP_MARK_H__


#define HTTP_SUCCESS       (0)          // 操作成功
#define HTTP_ERROR_UNKNOWN      (-1)         // 未知的错误
#define HTTP_ERROR_NETWORK      (-2)         // 网络连接失败
#define HTTP_ERROR_HTTP_HEAD    (-3)         // 未找到协议头 http || https 

#define HTTP_ERROR_SERVICE      (-1000)      // 服务器请求失败
#define HTTP_ERROR_LOGIN        (-1001)      // 登录失败
#define HTTP_ERROR_ID           (-1002)      // 企业ID错误
#define HTTP_ERROR_USER         (-1003)      // 帐号不存在
#define HTTP_ERROR_PASSWORD     (-1004)      // 密码错误

#define HTTP_ERROR_PARAMETER    (1)          // 参数错误
#define HTTP_ERROR_PHONE        (2)          // 电话号码错误
#define HTTP_ERROR_MESSAGE      (3)          // 短信有屏蔽字段
#define HTTP_ERROR_FUNCTION     (4)          // 当前平台不支持这个功能




#endif // __CLY_HTTP_MARK_H__