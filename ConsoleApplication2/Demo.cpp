#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPoints.h>
#include <vtkIdList.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkLine.h>
#include <vtkLineSource.h>
#include <vtkExtractCells.h>
#include <vtkModifiedBSPTree.h>

#include <vtkPolyDataMapper.h>
#include <vtkDatasetMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);



int main(int, char* [])
{
	vtkSmartPointer<vtkSphereSource> sphereSource =
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetPhiResolution(7);
	sphereSource->SetThetaResolution(15);
	sphereSource->Update();

	//������λ��
	vtkSmartPointer<vtkModifiedBSPTree> tree =
		vtkSmartPointer<vtkModifiedBSPTree>::New();
	tree->SetDataSet(sphereSource->GetOutput());

	//����λ����ֱ���ཻ
	double lineP0[3] = { -0.6,-0.6,-0.6 };
	double lineP1[3] = { .6, .6, .6 };
	vtkSmartPointer<vtkPoints>intersectPoints =
		vtkSmartPointer<vtkPoints>::New();

	vtkSmartPointer<vtkIdList>intersectCells =
		vtkSmartPointer<vtkIdList>::New();

	double tol = 1.e-8;
	tree->IntersectWithLine(lineP0, lineP1, tol,
		                    intersectPoints,
		                    intersectCells);

	std::cout << "NumPoints:" << intersectPoints->GetNumberOfPoints()
		      << std::endl;

	//��ʾ·���嵥
	double intersection[3];
	for (int i = 0; i < intersectPoints->GetNumberOfPoints(); i++)
	{
		intersectPoints->GetPoint(i, intersection);
		std::cout << "\tPoint Intersection" << i << ":"
			<< intersection[0] << ", "
			<< intersection[1] << ", "
			<< intersection[2] << std::endl;
	}

	std::cout << "NumCells:" << intersectCells->GetNumberOfIds()
		<< std::endl;

	vtkIdType cellId;
	for (int i = 0; i < intersectCells->GetNumberOfIds(); i++)
	{
		cellId = intersectCells->GetId(i);
		std::cout << "\tCellId " << i << ": "
			<< cellId << std::endl;
	}

	//��Ⱦ�ߣ�����ཻ����Ԫ
	vtkSmartPointer<vtkLineSource> lineSource =
		vtkSmartPointer<vtkLineSource>::New();
	lineSource->SetPoint1(lineP0);
	lineSource->SetPoint2(lineP1);

	vtkSmartPointer<vtkPolyDataMapper> lineMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	lineMapper->SetInputConnection(lineSource->GetOutputPort());
	vtkSmartPointer<vtkActor>lineActor =
		vtkSmartPointer<vtkActor>::New();
	lineActor->SetMapper(lineMapper);

	vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
	vtkSmartPointer<vtkActor>sphereActor =
		vtkSmartPointer<vtkActor>::New();
	sphereActor->SetMapper(sphereMapper);
	sphereActor->GetProperty()->SetRepresentationToWireframe();
	sphereActor->GetProperty()->SetColor(0.89, 0.81, 0.34);

	vtkSmartPointer<vtkExtractCells>cellSource =
		vtkSmartPointer<vtkExtractCells>::New();
	cellSource->SetInputConnection(sphereSource->GetOutputPort());
	cellSource->SetCellList(intersectCells);

	vtkSmartPointer<vtkDataSetMapper>cellMapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	cellMapper->SetInputConnection(cellSource->GetOutputPort());
	vtkSmartPointer<vtkActor>cellActor =
		vtkSmartPointer<vtkActor>::New();
	cellActor->SetMapper(cellMapper);
	cellActor->GetProperty()->SetColor(1.0, 0.3882, 0.2784);

	vtkSmartPointer<vtkRenderer>renderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow>renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->AddActor(lineActor);
	renderer->AddActor(sphereActor);
	renderer->AddActor(cellActor);
	renderer->SetBackground(.4, .5, .6);
	renderWindow->Render();
	renderWindowInteractor->Start();
	
	return	EXIT_SUCCESS;
}