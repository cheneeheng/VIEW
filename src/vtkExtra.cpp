/*
 * vtkExtra.cpp
 *
 *  Created on: Feb 16, 2017
 *      Author: chen
 */

#include "vtkExtra.h"

// ============================================================================
// MOUSE
// ============================================================================

class customMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
	public:
		static customMouseInteractorStyle* New();
		vtkTypeMacro(customMouseInteractorStyle,
				     vtkInteractorStyleTrackballCamera);

		void setLeftButton(bool pick){pick_ = pick;}

		void setColors(vector<unsigned char*> color){color_ = color;}

		void setLabels(vector<string> label){LABEL = label;}

		vector<string> getLabels(){return LABEL;}

		void setNumberOfLabels(int x){num_locations = x;}

		virtual void OnLeftButtonDown();

//    virtual void OnMiddleButtonDown()
//    {
//      std::cout << "Pressed middle mouse button." << std::endl;
//      // Forward events
//      vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
//    }
//
//    virtual void OnRightButtonDown()
//    {
//      std::cout << "Pressed right mouse button." << std::endl;
//      // Forward events
//      vtkInteractorStyleTrackballCamera::OnRightButtonDown();
//    }

	private:
		int 					num_locations;
		bool 					pick_;
		vector<string> 			LABEL;
		vector<unsigned char*> 	color_;

		void writeText(
			const char* text,
			double *rgb,
			int x,
			int y);
};

void customMouseInteractorStyle::OnLeftButtonDown()
{
	if(pick_)
	{
		//std::cout << "Pressed left mouse button." << std::endl;
		int* clickPos = this->GetInteractor()->GetEventPosition();

		// Pick from this location.
		vtkSmartPointer<vtkPointPicker>  picker = vtkSmartPointer<vtkPointPicker>::New();
		picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

		double rgb[3];
		if (picker->GetActor()!=0)
		{
			double* pos = picker->GetPickPosition();
			std::cout << ">>>>> Pick position (world coordinates) is: "
					  << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;

			picker->GetActor()
				  ->GetMapper()->GetInput()
				  ->GetPointData()->GetScalars()
				  ->GetTuple(picker->GetPointId(),rgb);

			//std::cout << "Pick position (color) is: "
			//		  << rgb[0] << " " << rgb[1] << " " << rgb[2] << std::endl;
			//std::cout << "Picked actor: " << picker->GetActor() << std::endl;
		}

		for(int i = 0;i<num_locations;i++)
			if (rgb[0]==color_[i+1][0] &&
				rgb[1]==color_[i+1][1] &&
				rgb[2]==color_[i+1][2])
			{
				cout << ">>>>> Enter label : ";
				string mystr; getline (cin, mystr);
				printf(">>>>> Label %02d : %s\n", i+1, mystr.c_str());

				if (!LABEL[i+1].empty())
				{
					cout << ">>>>> [WARNING] : Label has been given. Do you wish to overwrite? [Y/N]" << endl;
					while(1)
					{
						string mystr2; getline (cin, mystr2);
						if(!strcmp(mystr2.c_str(),"Y"))
						{
							cout << ">>>>> [WARNING] : Label has been overwritten. New label : " << mystr << endl;
							LABEL[i+1] = mystr;
							writeText(mystr.c_str(), rgb, 10, 470-10*(i+1));
							printf(">>>>> Pick a location...\n");
							break;
						}
						if(!strcmp(mystr2.c_str(),"N"))
						{
							cout << ">>>>> [WARNING] : Label has not been overwritten." << endl;
							printf(">>>>> Pick a location...\n");
							break;
						}
					}
				}
				else
				{
					LABEL[i+1] = mystr;
					writeText(mystr.c_str(), rgb, 10, 470-10*(i+1));
					printf(">>>>> Pick a location...\n");
					break;
				}
			}

		for(int i = 1;i<num_locations+1;i++)
		{
			// when there is no labeling at all
			if (LABEL.empty()) break;
			// check for completeness of labelling
			if (LABEL[i].empty()) break;
			// else
			if (i==num_locations)
			{
				cout << ">>>>> [WARNING] : Label has been fully labeled. Proceed? [Y/N]" << endl;
				string mystr3; getline (cin, mystr3);
				if(!strcmp(mystr3.c_str(),"Y"))
					this->GetInteractor()->TerminateApp();
				else
					printf(">>>>> Pick a location...\n");
			}
		}
		// Forward events, camera manipulation
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}
	else
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void customMouseInteractorStyle::writeText(
	const char* text,
	double *rgb,
	int x,
	int y)
{
	// Setup the text and add it to the renderer
	vtkSmartPointer<vtkTextActor> textActor;
	textActor = vtkSmartPointer<vtkTextActor>::New();
	textActor->SetInput ( text );
	textActor->SetPosition ( x, y );
	textActor->GetTextProperty()->SetFontSize ( 10 );
	textActor->GetTextProperty()->SetColor ( rgb[0]/255, rgb[1]/255, rgb[2]/255 );
	this->GetDefaultRenderer()->AddActor2D ( textActor );
	this->GetInteractor()->Render();
}

vtkStandardNewMacro(customMouseInteractorStyle);

// ============================================================================
// COLORCODE
// ============================================================================

void colorCode(
	vector<unsigned char*> &container_)
{
	// Setup colors
	unsigned char cw[]   = {255, 255, 255};
	unsigned char cy[]   = {255, 255, 0};
	unsigned char co[]   = {255, 127, 0};
	unsigned char cr[]   = {255, 0, 0};
	unsigned char clg[]  = {127, 255, 0};
	unsigned char cg[]   = {0, 255, 0};
	unsigned char cgb[]  = {0, 255, 127};
	unsigned char cc[]   = {0, 255, 255};
	unsigned char clb[]  = {0, 127, 255};
	unsigned char cb[]   = {0, 0, 255};
	unsigned char cpb[]  = {127, 0, 255};
	unsigned char cpr[]  = {255, 0, 127};
	copy(cw, 	cw+3, 	container_[0]);
	copy(cy, 	cy+3, 	container_[1]);
	copy(co, 	co+3, 	container_[2]);
	copy(cr, 	cr+3, 	container_[3]);
	copy(clg, 	clg+3,	container_[4]);
	copy(cg, 	cg+3, 	container_[5]);
	copy(cgb, 	cgb+3, 	container_[6]);
	copy(cc, 	cc+3, 	container_[7]);
	copy(clb, 	clb+3, 	container_[8]);
	copy(cb, 	cb+3, 	container_[9]);
	copy(cpb, 	cpb+3, 	container_[10]);
	copy(cpr, 	cpr+3, 	container_[11]);
}

vtkSmartPointer<vtkPolyDataMapper> dataPoints(
	vector<point_t> points_,
	int num_locations_,
	vector<unsigned char*> color_,
	bool cluster_)
{
	int num_locations = num_locations_;

	// Create the geometry of a point (the coordinate)
	// add point to polydata to create the vertices for glyph
	// creating the vertices with a small cube glyph
	// add points and vertices to polydata
	// giving the points color
	// Create a mapper and actor
	// Create a renderer, render window, and interactor
	// custom mouse
	// Setup the text and add it to the renderer
	vtkSmartPointer<vtkPoints> 					points;
	vtkSmartPointer<vtkPolyData> 				pointsPolydata;
	vtkSmartPointer<vtkVertexGlyphFilter>		vertexFilter;
	vtkSmartPointer<vtkPolyData> 				polydata;
	vtkSmartPointer<vtkUnsignedCharArray> 		colors;
	vtkSmartPointer<vtkPolyDataMapper>			mapper;
//	vtkSmartPointer<vtkActor> 					actor;
//	vtkSmartPointer<vtkRenderer> 				renderer;
//	vtkSmartPointer<vtkRenderWindow> 			renWin;
//	vtkSmartPointer<vtkRenderWindowInteractor> 	renWinInter;
//	vtkSmartPointer<customMouseInteractorStyle> style;
//	vtkSmartPointer<vtkTextActor> 				textActor;

	points 					= vtkSmartPointer<vtkPoints>::New();
	pointsPolydata 			= vtkSmartPointer<vtkPolyData>::New();
	vertexFilter			= vtkSmartPointer<vtkVertexGlyphFilter>::New();
	polydata 				= vtkSmartPointer<vtkPolyData>::New();
	colors 					= vtkSmartPointer<vtkUnsignedCharArray>::New();
	mapper 					= vtkSmartPointer<vtkPolyDataMapper>::New();

	for(int i=0;i<points_.size();i++)
		points->InsertNextPoint(points_[i].x, points_[i].y, points_[i].z);

	pointsPolydata->SetPoints(points);

#if VTK_MAJOR_VERSION <= 5
	vertexFilter->SetInputConnection(pointsPolydata->GetProducerPort());
	vertexFilter->Update();
#else
	vertexFilter->SetInputData(pointsPolydata);
	vertexFilter->Update();
#endif

	polydata->ShallowCopy(vertexFilter->GetOutput());

	if(cluster_)
	{
		colors->SetNumberOfComponents(3);
		colors->SetName ("Colors");
		for(int i=0;i<points_.size();i++)
		{
			if (points_[i].cluster_id < num_locations &&
				points_[i].cluster_id >= 0)
				colors->InsertNextTypedTuple(color_[points_[i].cluster_id+1]);
			else
				colors->InsertNextTypedTuple(color_[0]);
		}
		polydata->GetPointData()->SetScalars(colors);
	}

#if VTK_MAJOR_VERSION <= 5
	  mapper->SetInput(polydata);
#else
	  mapper->SetInputData(polydata);
#endif

	return mapper;
}

void showData(
	vector<point_t> points_,
	vector<string> &labels_,
	vector<unsigned char*> color_,
	bool cluster_,
	bool labeling_)
{
	int num_locations = labels_.size() - 1;

	vtkSmartPointer<vtkPolyDataMapper>			mapper;
	vtkSmartPointer<vtkActor> 					actor;
	vtkSmartPointer<vtkRenderer> 				renderer;
	vtkSmartPointer<vtkRenderWindow> 			renWin;
	vtkSmartPointer<vtkRenderWindowInteractor> 	renWinInter;
	vtkSmartPointer<customMouseInteractorStyle> style;
	vtkSmartPointer<vtkTextActor> 				textActor;

	mapper 					= vtkSmartPointer<vtkPolyDataMapper>::New();
	actor 					= vtkSmartPointer<vtkActor>::New();
	renderer 				= vtkSmartPointer<vtkRenderer>::New();
	renWin 			= vtkSmartPointer<vtkRenderWindow>::New();
	renWinInter 	= vtkSmartPointer<vtkRenderWindowInteractor>::New();
	style 					= vtkSmartPointer<customMouseInteractorStyle>::New();
//	textActor 				= vtkSmartPointer<vtkTextActor>::New();

	mapper =  dataPoints(points_, num_locations, color_, cluster_);

	actor->SetMapper(mapper);
	actor->GetProperty()->SetPointSize(3);
//	actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

	renWin->SetSize(WIN_WIDTH, WIN_HEIGHT); //(width, height)
	renWin->AddRenderer(renderer);
	renWinInter->SetRenderWindow(renWin);

	if(labeling_)
	{
		style->setLeftButton(true);
		textActor = vtkSmartPointer<vtkTextActor>::New();
		printf(">>>>> Pick a location...\n");
		if(!labels_.empty()) textActor->SetInput (labels_[0].c_str());
		textActor->SetPosition ( 10, (WIN_HEIGHT-20) );
		textActor->GetTextProperty()->SetFontSize ( FONT_SIZE );
		textActor->GetTextProperty()->SetColor ( 1.0, 1.0, 1.0 );
		renderer->AddActor2D (textActor);
	}
	else
	{
		style->setLeftButton(false);
		for(int i=0;i<num_locations+1;i++)
		{
			if(labels_.empty()) continue;
			if(labels_[i].empty()) continue;
			textActor = vtkSmartPointer<vtkTextActor>::New();
			textActor->SetInput(labels_[i].c_str());
			textActor->SetPosition(10, (WIN_HEIGHT-20)-i*FONT_SIZE);
			textActor->GetTextProperty()->SetFontSize(FONT_SIZE);
			textActor->GetTextProperty()
					 ->SetColor((double)color_[i][0]/255,
								(double)color_[i][1]/255,
								(double)color_[i][2]/255);
			renderer->AddActor2D(textActor);
		}
	}

	// Add the actor to the scene
	renderer->AddActor(actor);
	//renderer->SetBackground(nc->GetColor3d("MidnightBlue").GetData());
	style->SetDefaultRenderer(renderer);
	style->setNumberOfLabels(num_locations);
	style->setLabels(labels_);
	style->setColors(color_);
	renWinInter->SetInteractorStyle( style );
	renWin->Render();
	renWinInter->Start();

	labels_ = style->getLabels();
}

void plotData(
	vector<double> x,
	vector<double> y)
{
	vtkSmartPointer<vtkTable> 		table;
	vtkSmartPointer<vtkFloatArray> 	arrX;
	vtkSmartPointer<vtkFloatArray> 	arrY;
	vtkSmartPointer<vtkContextView> view;
	vtkSmartPointer<vtkChartXY> 	chart;

	table =	vtkSmartPointer<vtkTable>::New();
	arrX  = vtkSmartPointer<vtkFloatArray>::New();
	arrY  = vtkSmartPointer<vtkFloatArray>::New();
	view  = vtkSmartPointer<vtkContextView>::New();
	chart =	vtkSmartPointer<vtkChartXY>::New();

	// Create a table with some points in it
	arrX->SetName("X Axis");
	arrY->SetName("Y Axis");
	table->AddColumn(arrX);
	table->AddColumn(arrY);

	// Fill in the table with values
	int numPoints = x.size();
	table->SetNumberOfRows(numPoints);
	for (int i = 0; i < numPoints; ++i)
	{
		table->SetValue(i, 0, x[i]);
		table->SetValue(i, 1, y[i]);
	}

	// Set up the view
	view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	view->GetRenderer()->GetRenderWindow()->SetSize(1280,800); //(width, height)

	// Add multiple line plots, setting the colors etc
	view->GetScene()->AddItem(chart);

	vtkPlot *line;
	line = chart->AddPlot(vtkChart::LINE);
#if VTK_MAJOR_VERSION <= 5
  line->SetInput(table, 0, 1);
#else
  line->SetInputData(table, 0, 1);
#endif
  line->SetColor(255, 0, 0, 255);
  line->SetWidth(2.0);

//  // For dotted line, the line type can be from 2 to 5 for different dash/dot
//  // patterns (see enum in vtkPen containing DASH_LINE, value 2):
//#ifndef WIN32
//  line->GetPen()->SetLineType(vtkPen::DASH_LINE);
//#endif
//  // (ifdef-ed out on Windows because DASH_LINE does not work on Windows
//  //  machines with built-in Intel HD graphics card...)
//
//  //view->GetRenderWindow()->SetMultiSamples(0);

	// Start interactor
	view->GetInteractor()->Initialize();
	view->GetInteractor()->Start();
}

