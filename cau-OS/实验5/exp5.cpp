#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <time.h> 

unsigned _stdcall simulator(void *);
unsigned _stdcall inspector(void *);
LPVOID BASE_PTR;
int Actnum=0;

//����������Ҫ��������������ģ������ͽ��м�ص������߳�
int main(int argc, char* argv[])
{
	unsigned ThreadID[2];
	_beginthreadex(NULL,0,simulator,NULL,0,&ThreadID[0]);
	_beginthreadex(NULL,0,inspector,NULL,0,&ThreadID[1]);
	getchar();
	return 0;
} 
//ģ��һϵ�е��������Ϊһ���������߳����� 
unsigned _stdcall simulator(void *)
{
	DWORD OldProtect;
	int randnum;
	
	printf("Now the simulator procedure has been started.\n");
	//����һ�����������
	srand( (unsigned)time (NULL) );
	//��һ����ѭ���У�����������ƣ����Ͻ����������
	while(1)
	{
		Sleep(500);//��������ģ��ͼ�ص��ٶ�
		while(Actnum!=0)
		{
			Sleep(500);//�ȴ���ֱ������̲߳�׽����һ��ģ�⶯�����ټ�����һ������ 
		} 
	 randnum = 7&rand();
	 switch(randnum)  //���������е����ָ���ʹ��BASE_PTR�����ڹ������������亯����̬���������ĳ�������ɹ����򲻻ᱻ����̼߳�ص�
	 {
	 	case 0:
	 		if (BASE_PTR=VirtualAlloc(NULL,1024*32,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE))
	 		{
	 			Actnum=1;//���ı������ύ 
			 }
			break;
		case 1:
			if (VirtualFree(BASE_PTR,1024*32,MEM_COMMIT))
	 		{
	 			Actnum=2;//����ע�� 
			 }
			break;
		case 2:
			if (VirtualFree(BASE_PTR,0,MEM_RESERVE))
	 		{
	 			Actnum=3;//����ע�����ͷ����ռ� 
			 }
			break;
		case 3:
			if (VirtualProtect(BASE_PTR,1024*32,PAGE_READONLY,&OldProtect))
	 		{
	 			Actnum=4;//�ı�����ڴ�ҳ�ı��� 
			 }
			break;
		case 4:
			if (VirtualLock(BASE_PTR,1024*12))
	 		{
	 			Actnum=5;//���������ڴ�ҳ 
			 }
			break;
		case 5:
			if (BASE_PTR=VirtualAlloc(NULL,1024*32,MEM_RESERVE,PAGE_READWRITE))
	 		{
	 			Actnum=6;//���ı��� 
			 }
			break;
		default:
			break;
	  } //end of 'switch'
	} //end of 'while'
	return 0;
} 

//ͨ��һ��ȫ�ֱ�����������һģ���̵߳�ģ������ͨ���ʵ�����Ϣ��ѯ���������洢��ʹ�úͻ����������
unsigned _stdcall inspector(void *)
{
	int QuOut=0;
	char para1[3000];
	MEMORYSTATUS Vmeminfo;
	char tempstr[100];
	MEMORY_BASIC_INFORMATION inspectorinfo1;
	int structsize = sizeof(MEMORY_BASIC_INFORMATION);
	
	printf("Hi , now inspector begin to work\n");
	//��һ����ѭ���в���ͨ��һ��ȫ�ֱ��������������������ģ���߳��Ƿ����µĶ���������У�ͨ����API��������Ӧ��洦��ͨ������BASE_PTRʵ�֣�����Ϣ���м�飬�Ӷ���֤�ö����Դ洢ʹ�õ�Ӱ��
	while(1)
	{
		Sleep(1000);
		if(Actnum!=0)
		{
			//ͨ��ȫ�ֱ�������������Actnum����ȡ��һ����涯�������ͼ���Ӧ��������Ϣ��ͷ��
			switch(Actnum)
			{
				case 1:
					memset (&inspectorinfo1, 0 , structsize);
					VirtualQuery((LPVOID)BASE_PTR,&inspectorinfo1,structsize);
					strcpy(para1,"Ŀǰִ�ж��������ı������ύ\n");
					break;
				case 2:
					memset (&inspectorinfo1, 0 , structsize);
					VirtualQuery((LPVOID)BASE_PTR,&inspectorinfo1,structsize);
					strcpy(para1,"Ŀǰִ�ж��������ĳ���\n");
					break;	
				case 3:
					memset (&inspectorinfo1, 0 , structsize);
					VirtualQuery((LPVOID)BASE_PTR,&inspectorinfo1,structsize);
					strcpy(para1,"Ŀǰִ�ж��������ĳ��䲢�ͷ����ռ�\n");
					break;	
				case 4:
					memset (&inspectorinfo1, 0 , structsize);
					VirtualQuery((LPVOID)BASE_PTR,&inspectorinfo1,structsize);
					strcpy(para1,"Ŀǰִ�ж������ı�����ڴ�ҳ�ı���\n");
					break;
				case 5:
					memset (&inspectorinfo1, 0 , structsize);
					VirtualQuery((LPVOID)BASE_PTR,&inspectorinfo1,structsize);
					strcpy(para1,"Ŀǰִ�ж�������������ڴ�ҳ\n");
					break;	
				case 6:
					memset (&inspectorinfo1, 0 , structsize);
					VirtualQuery((LPVOID)BASE_PTR,&inspectorinfo1,structsize);
					strcpy(para1,"Ŀǰִ�ж��������ı���\n");
					break;
				default:
				break;	
			 } 
			 //ʵʱ��ʾ�̶���ʽ����ز��ϣ�ͨ��Ŀǰ��ص��Ķ���������������ַ����ظû����Ӧ�洢�ռ��Ӱ��
			sprintf(tempstr,"��ʼ��ַ: 0X%x\n",inspectorinfo1.BaseAddress);
			strcat(para1,tempstr);
			sprintf(tempstr,"�����С��Ŀǰָ�봦��ǰͬһ���ԵĿ飩: 0X%x\n",inspectorinfo1.RegionSize);
			strcat(para1,tempstr); 
			sprintf(tempstr,"Ŀǰ״̬: 0X%x\n",inspectorinfo1.State);
			strcat(para1,tempstr);
			sprintf(tempstr,"����ʱ���ʱ���: 0X%x\n",inspectorinfo1.AllocationProtect);
			strcat(para1,tempstr);
			sprintf(tempstr,"��ǰ���ʱ���: 0X%x\n",inspectorinfo1.Protect);
			strcat(para1,tempstr);
			strcat(para1,"(״̬:10000����δ����;1000�����ύ;2000������;)\n");
			strcat(para1,"(������ʽ��0��������;1�����ֹ����;2����ֻ��;4�����д;\n10�����ִ��;20����ɶ���ִ��;40����ɶ�д��ִ��)\n*********\n");
			
			//ȫ����Ϣ������Ŀǰϵͳ�͵�ǰ���̵Ĵ洢ʹ���������
			GlobalMemoryStatus(&Vmeminfo);
			strcat(para1,"��ǰ����洢ͳ������\n");
			sprintf(tempstr,"�����ڴ�����:%lu(BYTES)\n",Vmeminfo.dwTotalPhys);//���е���������Ϊd����Ϊlu 
			strcat(para1,tempstr);
			sprintf(tempstr,"���������ڴ���:%lu(BYTES)\n",Vmeminfo.dwAvailPhys); //���е���������Ϊd����Ϊlu 
			strcat(para1,tempstr);
			sprintf(tempstr,"ҳ���ļ�����:%lu(BYTES)\n",Vmeminfo.dwTotalPageFile);//���е���������Ϊd����Ϊlu 
			strcat(para1,tempstr);
			sprintf(tempstr,"����ҳ���ļ���:%lu(BYTES)\n",Vmeminfo.dwAvailPageFile);//���е���������Ϊd����Ϊlu 
			strcat(para1,tempstr);
			sprintf(tempstr,"���ռ�����:%lu(BYTES)\n",Vmeminfo.dwTotalVirtual);//���е���������Ϊd����Ϊlu 
			strcat(para1,tempstr);
			sprintf(tempstr,"�������ռ���:%lu(BYTES)\n",Vmeminfo.dwAvailVirtual);//���е���������Ϊd����Ϊlu 
			strcat(para1,tempstr);
			sprintf(tempstr,"����洢ʹ�ø���:%%%lu\n\n\n\n",Vmeminfo.dwMemoryLoad);//���е���������Ϊd����Ϊlu 
			strcat(para1,tempstr);
			printf("%s",para1);//��ʾ��������
			//(�������ͬʱ���������ݼ�¼����־�ļ�)
			Actnum=0;//֪ͨģ���߳̿��Խ�����һ��ģ�⶯��
			Sleep(500);//����ģ��ͼ�ص������ٶ� 
		}//for if 
	 } //for while
	 return 0;
}
