std::pair<int,int> findAboveAndBelowNonzeroBinsX(TH2F *hist, int xBin, int yBin);
std::pair<int,int> findAboveAndBelowNonzeroBinsY(TH2F *hist, int xBin, int yBin);

TH2F* TH2_Interpolate_hist(TH2F *hist){

  TH2F *histInterp = (TH2F*)hist->Clone();
  
  for(int i=1; i<=histInterp->GetNbinsX(); i++){
    for(int j=1; j<=histInterp->GetNbinsY(); j++){
      double y = histInterp->GetYaxis()->GetBinCenter(j);
      std::pair<int,int> prevNextY = findAboveAndBelowNonzeroBinsY(histInterp,i,j);
      bool useY = true;
      if(prevNextY.first < 0 || prevNextY.second < 0) useY = false;

        if(useY){

	  double ySlope = (histInterp->GetBinContent(i,prevNextY.second) - histInterp->GetBinContent(i,prevNextY.first))/(histInterp->GetYaxis()->GetBinCenter(prevNextY.second) - histInterp->GetYaxis()->GetBinCenter(prevNextY.first));
	  double yAvg = ySlope*(y - histInterp->GetYaxis()->GetBinCenter(prevNextY.first)) + histInterp->GetBinContent(i,prevNextY.first);

	  histInterp->SetBinContent(i,j,yAvg);
	  
	}

      
    }
  }


  for(int j=1; j<=histInterp->GetNbinsY(); j++){
    for(int i=1; i<=histInterp->GetNbinsX(); i++){
      double x = histInterp->GetXaxis()->GetBinCenter(i);
      std::pair<int,int> prevNextX = findAboveAndBelowNonzeroBinsX(histInterp,i,j);
      bool useX = true;
      if(prevNextX.first < 0 || prevNextX.second < 0) useX = false;

        if(useX){

	  double xSlope = (histInterp->GetBinContent(prevNextX.second,j) - histInterp->GetBinContent(prevNextX.first,j))/(histInterp->GetXaxis()->GetBinCenter(prevNextX.second) - histInterp->GetXaxis()->GetBinCenter(prevNextX.first));
	  double xAvg = xSlope*(x - histInterp->GetXaxis()->GetBinCenter(prevNextX.first)) + histInterp->GetBinContent(prevNextX.first,j);

	  histInterp->SetBinContent(i,j,xAvg);
	  
	}

      
    }
  }


  return histInterp;
  
}


std::pair<int,int> findAboveAndBelowNonzeroBinsY(TH2F *hist, int xBin, int yBin){

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



  std::pair<int,int> prevNextY = {prevY,nextY};

  return prevNextY;

}


std::pair<int,int> findAboveAndBelowNonzeroBinsX(TH2F *hist, int xBin, int yBin){

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



  std::pair<int,int> prevNextX = {prevX,nextX};

  return prevNextX;

}
