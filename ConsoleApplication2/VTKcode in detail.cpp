#include <vtkSmartPointer.h>//vtk����ָ����
//vtkSmartPointer<ָ�������������> ָ�������=vtkSmartPointer<ָ�������������>::New();
#include <vtkRenderWindow.h>//vtk�����������л��ƴ��ڵĳ������
#include <vtkRenderer.h>//�������������Ⱦ����
#include <vtkRenderWindowInteractor.h>//�ṩƽ̨������Ӧ��꣬���̺�ʱ���¼��Ľ�������
#include <vtkInteractorStyleTrackballCamera.h>//��������һ����ʽ
#include <vtkCylinderSource.h>//����һ����������Ⱦ����ԭ�������
#include <vtkPolyDataMapper.h>//vtk������ӳ������������Ⱦ����μ�������
#include <vtkActor.h>//���𳡾��еļ�������

int main()
{
	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetHeight(3.0);//��������ĸ�
	cylinder->SetRadius(1.0);//��������ĺ����뾶
	cylinder->SetResolution(10);//������������ĵȶ���α���

	vtkSmartPointer<vtkPolyDataMapper>cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());//��cylinder�õ���������ٽ������뵽cylinderMapper
	//SetInputConnection()�������ݽӿڣ�GetOutputPort()������ݽӿ�

	vtkSmartPointer<vtkActor>cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinderMapper);
	//��cyinderActot��Mapper(vtkMapper)��������ΪcylinderMapper

	vtkSmartPointer<vtkRenderer>renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(cylinderActor);//�����Ͷ�����ӵ���Ⱦ��������
	renderer->SetBackground(0.1, 0.2, 0.4);//��RGB��ʽ���ñ�����ɫ

	vtkSmartPointer<vtkRenderWindow>renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);//����AddRenderer() ���vtkRenderer���ͻ�����
	renWin->SetSize(300, 300);//����SetSize() ���ô��ڵĴ�С��������Ϊ��λ

	vtkSmartPointer<vtkRenderWindowInteractor>iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	//��Ϣ��ͨ����Ⱦ���ڲ���ģ������������������Ⱦ����

	vtkSmartPointer<vtkInteractorStyleTrackballCamera>style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);
	//���彻�����Ľ�����ʽ
	
	iren->Initialize();//��ʼ��
	iren->Start();//��ʼ����ʵ����Ӧѭ��

	return 0;
}