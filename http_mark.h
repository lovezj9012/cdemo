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

#ifndef __CLY_HTTP_MARK_H__
#define __CLY_HTTP_MARK_H__


#define HTTP_SUCCESS       (0)          // �����ɹ�
#define HTTP_ERROR_UNKNOWN      (-1)         // δ֪�Ĵ���
#define HTTP_ERROR_NETWORK      (-2)         // ��������ʧ��
#define HTTP_ERROR_HTTP_HEAD    (-3)         // δ�ҵ�Э��ͷ http || https 

#define HTTP_ERROR_SERVICE      (-1000)      // ����������ʧ��
#define HTTP_ERROR_LOGIN        (-1001)      // ��¼ʧ��
#define HTTP_ERROR_ID           (-1002)      // ��ҵID����
#define HTTP_ERROR_USER         (-1003)      // �ʺŲ�����
#define HTTP_ERROR_PASSWORD     (-1004)      // �������

#define HTTP_ERROR_PARAMETER    (1)          // ��������
#define HTTP_ERROR_PHONE        (2)          // �绰�������
#define HTTP_ERROR_MESSAGE      (3)          // �����������ֶ�
#define HTTP_ERROR_FUNCTION     (4)          // ��ǰƽ̨��֧���������




#endif // __CLY_HTTP_MARK_H__