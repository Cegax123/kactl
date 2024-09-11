ll cross(point a,point b){
    return a.x*b.y-a.y*b.x;
}
void reorder_polygon(vector<point> & P){
    size_t pos = 0;
    for(size_t i = 1; i < P.size(); i++){
        if(P[i].x < P[pos].x || (P[i].x == P[pos].x && P[i].y < P[pos].y))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}
vector<point> minkowski(vector<point> P, vector<point> Q){
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    // main part
    vector<point> result;
    size_t i = 0, j = 0;
    while(i < P.size() - 2 || j < Q.size() - 2){
        result.push_back(P[i]+Q[j]);
        auto cros = cross(P[i + 1]-P[i],Q[j + 1]-Q[j]);
        if(cros >= 0 && i < P.size() - 2) ++i;
        if(cros <= 0 && j < Q.size() - 2) ++j;
    }
    return result;
}

