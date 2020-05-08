#include <vtkSmartPointer.h>//vtk智能指针类
//vtkSmartPointer<指向对象类型名称> 指针变量名=vtkSmartPointer<指向对象类型名称>::New();
#include <vtkRenderWindow.h>//vtk绘制器，进行绘制窗口的抽象基类
#include <vtkRenderer.h>//负责管理场景的渲染过程
#include <vtkRenderWindowInteractor.h>//提供平台独立响应鼠标，键盘和时钟事件的交互机制
#include <vtkInteractorStyleTrackballCamera.h>//交互器的一种样式
#include <vtkCylinderSource.h>//生成一个中心在渲染场景原点的柱体
#include <vtkPolyDataMapper.h>//vtk聚数据映射器，用于渲染多边形几何数据
#include <vtkActor.h>//负责场景中的几何数据

int main()
{
	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetHeight(3.0);//设置柱体的高
	cylinder->SetRadius(1.0);//设置柱体的横截面半径
	cylinder->SetResolution(10);//设置柱体横截面的等多边形边数

	vtkSmartPointer<vtkPolyDataMapper>cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());//从cylinder得到输出数据再将其输入到cylinderMapper
	//SetInputConnection()输入数据接口，GetOutputPort()输出数据接口

	vtkSmartPointer<vtkActor>cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinderMapper);
	//将cyinderActot的Mapper(vtkMapper)对象设置为cylinderMapper

	vtkSmartPointer<vtkRenderer>renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(cylinderActor);//将类型对象添加到渲染场景当中
	renderer->SetBackground(0.1, 0.2, 0.4);//用RGB格式设置背景颜色

	vtkSmartPointer<vtkRenderWindow>renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);//调用AddRenderer() 添加vtkRenderer类型绘制器
	renWin->SetSize(300, 300);//调用SetSize() 设置窗口的大小，以像素为单位

	vtkSmartPointer<vtkRenderWindowInteractor>iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	//消息是通过渲染窗口捕获的，必须给交互器设置渲染窗口

	vtkSmartPointer<vtkInteractorStyleTrackballCamera>style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);
	//定义交互器的交互样式
	
	iren->Initialize();//初始化
	iren->Start();//开始静茹实践响应循环

	return 0;
}