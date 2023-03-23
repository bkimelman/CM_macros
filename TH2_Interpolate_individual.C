std::pair<int,int> findAboveAndBelowNonzeroBinsX(TH2F *hist, int xBin, int yBin);
std::pair<int,int> findAboveAndBelowNonzeroBinsY(TH2F *hist, int xBin, int yBin);

double TH2_Interpolate_individual(TH2F *hist, double x, double y){
  int binX = hist->GetXaxis()->FindBin(x);
  int binY = hist->GetYaxis()->FindBin(y);

  TH2F *hist2 = (TH2F*)hist->Clone();

  
  //first do R (y) interpolating then phi (x)

  std::pair<int,int> prevNextY = findAboveAndBelowNonzeroBinsY(hist,binX,binY);
  bool useY = true;
  if(prevNextY.first < 0 || prevNextY.second < 0) useY = false;


  

  std::pair<int,int> prevNextX = findAboveAndBelowNonzeroBinsX(hist,binX,binY);

  
  bool useX = true;

  if(above.first < 0 || below.first < 0) useX = false;

  double xAvg = 0;
  double yAvg = 0;

  if(useX){

    double xSlope = (hist->GetBinContent(above.first,binY) - hist->GetBinContent(below.first,binY))/(hist->GetXaxis()->GetBinCenter(above.first) - hist->GetXaxis()->GetBinCenter(below.first));
    xAvg = xSlope*(x - hist->GetXaxis()->GetBinCenter(below.first)) + hist->GetBinContent(below.first,binY);
    
  }

  if(useY){

    double ySlope = (hist->GetBinContent(binX,above.second) - hist->GetBinContent(binX,below.second))/(hist->GetYaxis()->GetBinCenter(above.second) - hist->GetYaxis()->GetBinCenter(below.second));
    yAvg = ySlope*(y - hist->GetYaxis()->GetBinCenter(below.second)) + hist->GetBinContent(binX,below.second);
    
  }

  if(useX && useY) return 0.5*(xAvg + yAvg);
  else if(useX) return xAvg;
  else if(useY) return yAvg;
  else return 0.0;
		 
  
  /*
  double x1;
  double y1;
  double x2;
  double y2;
  
  int quad = 0;

  double dx = hist->GetXaxis()->GetBinUpEdge(binX)-x;
  double dy = hist->GetYaxis()->GetBinUpEdge(binY)-y;
  if(dx <= hist->GetXaxis()->GetBinWidth(binX)/2 && dy <= hist->GetYaxis()->GetBinWidth(binY)/2) quad = 1;
  else if(dx > hist->GetXaxis()->GetBinWidth(binX)/2 && dy <= hist->GetYaxis()->GetBinWidth(binY)/2) quad = 2;
  else if(dx > hist->GetXaxis()->GetBinWidth(binX)/2 && dy > hist->GetYaxis()->GetBinWidth(binY)/2) quad = 3;
  else if(dx <= hist->GetXaxis()->GetBinWidth(binX)/2 && dy > hist->GetYaxis()->GetBinWidth(binY)/2) quad = 4;

  std::pair<int,int> nextXY = findNextNonzeroBins(hist,binX,binY,quad);

  cout << "quad: " << quad << "   next X: " << nextXY.first << "   next Y: " << nextXY.second << endl;
  
  switch(quad){
  case 1:
    x1 = hist->GetXaxis()->GetBinCenter(binX);
    y1 = hist->GetYaxis()->GetBinCenter(binY);
    x2 = hist->GetXaxis()->GetBinCenter(nextXY.first);
    y2 = hist->GetYaxis()->GetBinCenter(nextXY.second);
    break;
  case 2:
    x2 = hist->GetXaxis()->GetBinCenter(binX);
    y1 = hist->GetYaxis()->GetBinCenter(binY);
    x1 = hist->GetXaxis()->GetBinCenter(nextXY.first);
    y2 = hist->GetYaxis()->GetBinCenter(nextXY.second);
    break;
  case 3:
    x2 = hist->GetXaxis()->GetBinCenter(binX);
    y2 = hist->GetYaxis()->GetBinCenter(binY);
    x1 = hist->GetXaxis()->GetBinCenter(nextXY.first);
    y1 = hist->GetYaxis()->GetBinCenter(nextXY.second);
    break;
  case 4:
    x1 = hist->GetXaxis()->GetBinCenter(binX);
    y2 = hist->GetYaxis()->GetBinCenter(binY);
    x2 = hist->GetXaxis()->GetBinCenter(nextXY.first);
    y1 = hist->GetYaxis()->GetBinCenter(nextXY.second);
    break;
  }

  
  int binX1 = hist->GetXaxis()->FindBin(x1);
  int binX2 = hist->GetXaxis()->FindBin(x2);
  int binY1 = hist->GetYaxis()->FindBin(y1);
  int binY2 = hist->GetYaxis()->FindBin(y2);

  double xSlope = (hist->GetBinContent(binX2,binY) - hist->GetBinContent(binX1,binY))/(x2-x1);
  double ySlope = (hist->GetBinContent(binX,binY2) - hist->GetBinContent(binX,binY1))/(y2-y1);

  double zx = xSlope*(x-x1)+hist->GetBinContent(binX1,binY);
  double zy = ySlope*(y-y1)+hist->GetBinContent(binX,binY1);
  */

  
  /*
    double q11 = hist->GetBinContent(binX1,binY1);
  double q12 = hist->GetBinContent(binX1,binY2);
  double q21 = hist->GetBinContent(binX2,binY1);
  double q22 = hist->GetBinContent(binX2,binY2);


  double xAvg = 
  

  double d = 1.0*(x2-x1)*(y2-y1);

  double f = 1.0*q11/d*(x2-x)*(y2-y) + 1.0*q21/d*(x-x1)*(y2-y) + 1.0*q12/d*(x2-x)*(y-y1) + 1.0*q22/d*(x-x1)*(y-y1);

  return f;
  */

  //  return 0.5*(zx + zy);
}

std::pair<int,int> findAboveAndBlowNonzeroBinsY(TH2F *hist, int xBin, int yBin){

  int prevY = -1;
  int nextY = -1;

  for(int i=yBin-1; i>=1; i--){
    if(hist->GetBinContent(xBin,i) != 0.0){
      prevY = i;
      break;
    }
  }
  

  
  for(int i=yBin; i<hist->GetNbinsY(); i++){
    if(hist->GetBinContent(xBin,i) != 0.0){
      nextY = i;
      break;
    }
  }


  
  std::pair<int,int> pervNextY = {prevY,nextY};

  return prevNextY;
  
}


std::pair<int,int> findAboveAndBlowNonzeroBinsX(TH2F *hist, int xBin, int yBin){

  int prevX = -1;
  int nextX = -1;

  for(int i=xBin-1; i>=1; i--){
    if(hist->GetBinContent(i,yBin) != 0.0){
      prevX = i;
      break;
    }
  }
  

  
  for(int i=xBin; i<hist->GetNbinsX(); i++){
    if(hist->GetBinContent(i,yBin) != 0.0){
      nextX = i;
      break;
    }
  }


  
  std::pair<int,int> pervNextX = {prevX,nextX};

  return prevNextX;
  
}

