#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;
typedef pair<double, double> Point;

typedef pair<pair<Point,Point>, double > Pair;

class ClosedPair
{
public:
	ClosedPair()
	{

	}
	/*
	计算两点间距离
	*/
private:
	static double dist(Point _Tmp_first, Point _Tmp_second)
	{
		double distPowX = pow((_Tmp_first.first - _Tmp_second.first), 2);
		double distPowY = pow((_Tmp_first.second - _Tmp_second.second), 2);
		return sqrt(distPowX + distPowY);
	}
private:
	/*
	排序规则
	*/
	static bool compX(const Point& point1,const Point& point2)
	{
		return point1.first < point2.first;
	}
	static bool compY(const Point& point1, const Point& point2)
	{
		return point1.second < point2.second;
	}


	/*
	重构
	*/
	static vector<Point> merge(vector<Point> c, vector<Point> d, int l, int m, int r)
	{
		int i = l, j = m + 1, k = l;
		while ((i <= m) && (j <= r))
		{
			if (c[i] <= c[j])
			{
				d[k++] = c[i++];
			}
			else
			{
				d[k++] = c[j++];
			}
		}

		if (i>m)
		{
			for (int q = j; q <= r; q++)
			{
				d[k++] = c[q];
			}
		}
		else
		{
			for (int q = i; q <= m; q++)
			{
				d[k++] = c[q];
			}
		}
		return d;
	}


	/*
	求解
	*/
	void closestPair(vector<Point> X, vector<Point> Y, vector<Point> Z, int l, int r, Point& a, Point& b, double& d)
	{
		if (r - l == 1) //两点的情形   
		{
			a = X[l];
			b = X[r];
			d = dist(X[l], X[r]);
			return;
		}

		if (r - l == 2) //3点的情形   
		{
			double d1 = dist(X[l], X[l + 1]);
			double d2 = dist(X[l + 1], X[r]);
			double d3 = dist(X[l], X[r]);

			if (d1 <= d2 && d1 <= d3)
			{
				a = X[l];
				b = X[l + 1];
				d = d1;
				return;
			}

			if (d2 <= d3)
			{
				a = X[l + 1];
				b = X[r];
				d = d2;
			}
			else {
				a = X[l];
				b = X[r];
				d = d3;
			}
			return;
		}

		//多于3点的情形，用分治法   
		int m = (l + r) / 2;
		int f = l, g = m + 1;

		for (int i = l; i <= r; i++)
		{
			if (Y[i].first>m) Z[g++] = Y[i];
			else Z[f++] = Y[i];
		}

		closestPair(X, Z, Y, l, m, a, b, d);
		double dr;

		Point ar, br;
		closestPair(X, Z, Y, m + 1, r, ar, br, dr);

		if (dr<d)
		{
			a = ar;
			b = br;
			d = dr;
		}

		merge(Z, Y, l, m, r);//重构数组Y  

		//d矩形条内的点置于Z中  
		int k = l;
		for (int i = l; i <= r; i++)
		{
			if (abs(X[m].first - Y[i].first)<d)
			{
				Z[k++] = Y[i];
			}
		}
	}
public:
	Pair cpair(vector<Point> x)
	{
		sort(x.begin(), x.end(),compX);
		vector<Point> y = x;
		sort(y.begin(), y.end(), compY);
		vector<Point> z;

		for (int i = 0; i <= (int)x.size(); i++)
		{
			z.push_back(make_pair(0, 0));
		}
		Point a, b; double d;
		closestPair(x, y, z, 0, x.size()-1,a,b,d);
		Pair p;
		p.first.first = a; p.first.second = b; p.second = d;
		return p;
	}


};

int main()
{
	vector<Point> vec;
	Point point;
	cout << "Sum of point number:";
	int n;
	cin >> n;
	cout << "Point is:\n";
	for (int i = 0; i < n; i++)
	{
		point.first = ((rand()%10000)*0.001);
		point.second = ((rand() % 10000)*0.001);
		vec.push_back(point);
		cout << "<" << point.first << "," << point.second << ">  ";
		if (i % 3 == 0 && i != 0)
		{
			cout << "\n";
		}
	}

	ClosedPair closest;
	Pair p=closest.cpair(vec);
	Point point1 = p.first.first;
	Point point2 = p.first.second;
	cout << "\nThe closest point are:";
	cout << "<" << point1.first << "," << point1.second << ">  , <" << point2.first << "," << point2.second << ">\n";
	cout << "The distance is:" << p.second << "\n";
	return 0;  
}
