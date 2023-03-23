std::pair<int,int> findNextNonzeroBins(TH2F *hist, int xBin, int yBin, int quad);
std::pair<int,int> findBelowNonzeroBins(TH2F *hist, int xBin, int yBin);
std::pair<int,int> findAboveNonzeroBins(TH2F *hist, int xBin, int yBin);

double TH2_Interpolate(TH2F *hist, double x, double y){
  int binX = hist->GetXaxis()->FindBin(x);
  int binY = hist->GetYaxis()->FindBin(y);


  std::pair<int,int> above = findAboveNonzeroBins(hist,binX,binY);
  std::pair<int,int> below = findBelowNonzeroBins(hist,binX,binY);

  //  cout << "above x: " << above.first << "   above y: " << above.second << endl;
  //  cout << "below x: " << below.first << "   below y: " << below.second << endl;
  
  bool useX = true;
  bool useY = true;

  if(above.first < 0 || below.first < 0) useX = false;
  if(above.second < 0 || below.second < 0) useY = false;

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

std::pair<int,int> findAboveNonzeroBins(TH2F *hist, int xBin, int yBin){

  int nextX = -1;
  int nextY = -1;

  for(int i=xBin; i<hist->GetNbinsX(); i++){
    if(hist->GetBinContent(i,yBin) != 0.0){
      nextX = i;
      break;
    }
  }

  for(int i=yBin; i<hist->GetNbinsY(); i++){
    if(hist->GetBinContent(xBin,i) != 0.0){
      nextY = i;
      break;
    }
  }

  std::pair<int,int> nextXY = {nextX,nextY};

  return nextXY;
  
}

std::pair<int,int> findBelowNonzeroBins(TH2F *hist, int xBin, int yBin){

  int prevX = -1;
  int prevY = -1;

  for(int i=xBin-1; i>=1; i--){
    if(hist->GetBinContent(i,yBin) != 0.0){
      prevX = i;
      break;
    }
  }

  for(int i=yBin-1; i>=1; i--){
    if(hist->GetBinContent(xBin,i) != 0.0){
      prevY = i;
      break;
    }
  }

  std::pair<int,int> prevXY = {prevX,prevY};

  return prevXY;
  
}

std::pair<int,int> findNextNonzeroBins(TH2F *hist, int xBin, int yBin, int quad){

  int nextX = -1;
  int nextY = -1;
  
  //get next bin x
  if(quad == 2 || quad == 4){
    for(int i=xBin+1; i<=hist->GetNbinsX(); i++){
      if(hist->GetBinContent(i,yBin) != 0.0){
	nextX = i;
	break;
      }
    }
  }else{
    for(int i=xBin-1; i>=1; i--){
      if(hist->GetBinContent(i,yBin) != 0.0){
	nextX = i;
	break;
      }
    }

  }


  //get next bin y
  if(quad == 1 || quad == 2){
    for(int i=yBin+1; i<=hist->GetNbinsY(); i++){
      if(hist->GetBinContent(xBin,i) != 0.0){
	nextY = i;
	break;
      }
    }
  }else{
    for(int i=yBin-1; i>=1; i--){
      if(hist->GetBinContent(xBin,i) != 0.0){
	nextY = i;
	break;
      }
    }

  }

  std::pair<int,int> nextXY;
  nextXY.first = nextX;
  nextXY.second = nextY;

  return nextXY;
  
}
