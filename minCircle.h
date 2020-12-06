// ID1	ID2

#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>

using namespace std;

// ------------ DO NOT CHANGE -----------
class Point{
public:
	float x,y;
	Point(float x,float y):x(x),y(y){}
};

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

// implement


// you may add helper functions here



/* 
 * Smallest enclosing circle - Library (C++)
 * 
 * Copyright (c) 2020 Project Nayuki
 * https://www.nayuki.io/page/smallest-enclosing-circle
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program (see COPYING.txt and COPYING.LESSER.txt).
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <random>

using std::size_t;
using std::vector;
using std::max;
using std::min;


/*---- omer start ----*/

Point subtract(const Point &myPoint, const Point &p) {
	return Point{myPoint.x - p.x, myPoint.y - p.y};
}


double distance(const Point &myPoint, const Point &p) {
	return std::hypot(myPoint.x - p.x, myPoint.y - p.y);
}


double cross(const Point &myPoint, const Point &p) {
	return myPoint.x * p.y - myPoint.y * p.x;
}



/*---- Members of struct Circle ----*/

//const Circle Circle::INVALID{Point{0, 0}, -1};

const double MULTIPLICATIVE_EPSILON = 1 + 1e-14;


bool contains(const Circle &myCircle, const Point &p) {
	return distance(myCircle.center, p) <= myCircle.radius * MULTIPLICATIVE_EPSILON;
}


bool contains(const Circle &myCircle, const vector<Point> &ps) {
	for (const Point &p : ps) {
		if (!contains(myCircle, p))
			return false;
	}
	return true;
}
Circle makeDiameter(const Point &a, const Point &b) {
	Point c = Point((a.x + b.x) / 2, (a.y + b.y) / 2);
	float dis = max(distance(c, a), distance(c, b));
	Circle circ = Circle(c, dis);
	return circ;
}

Circle makeCircumcircle(const Point &a, const Point &b, const Point &c) {
	// Mathematical algorithm from Wikipedia: Circumscribed circle
	double ox = (min(min(a.x, b.x), c.x) + max(max(a.x, b.x), c.x)) / 2;
	double oy = (min(min(a.y, b.y), c.y) + max(max(a.y, b.y), c.y)) / 2;
	double ax = a.x - ox,  ay = a.y - oy;
	double bx = b.x - ox,  by = b.y - oy;
	double cx = c.x - ox,  cy = c.y - oy;
	double d = (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) * 2;
	if (d == 0)
		return Circle(Point(0,0), 0);
	double x = ((ax*ax + ay*ay) * (by - cy) + (bx*bx + by*by) * (cy - ay) + (cx*cx + cy*cy) * (ay - by)) / d;
	double y = ((ax*ax + ay*ay) * (cx - bx) + (bx*bx + by*by) * (ax - cx) + (cx*cx + cy*cy) * (bx - ax)) / d;
	Point p = Point(ox + x, oy + y);
	double r = max(max(distance(p, a), distance(p, b)), distance(p, c));
	return Circle(p, r);
}


/*---- Smallest enclosing circle algorithm ----*/

static Circle makeSmallestEnclosingCircleOnePoint (const vector<Point> &points, size_t end, const Point &p);
static Circle makeSmallestEnclosingCircleTwoPoints(const vector<Point> &points, size_t end, const Point &p, const Point &q);

static std::default_random_engine randGen((std::random_device())());



// Initially: No boundary points known
Circle makeSmallestEnclosingCircle(const vector<Point> &points) {
	// Clone list to preserve the caller's data, randomize order
	vector<Point> shuffled = points;
	std::shuffle(shuffled.begin(), shuffled.end(), randGen);
	
	// Progressively add points to circle or recompute circle
	Circle c = Circle(Point(0,0), 0);
	for (size_t i = 0; i < shuffled.size(); i++) {
		const Point &p = shuffled.at(i);
		if (c.radius < 0 || !contains(c, p))
			c = makeSmallestEnclosingCircleOnePoint(shuffled, i + 1, p);
	}
	return c;
}



// One boundary point known
static Circle makeSmallestEnclosingCircleOnePoint(const vector<Point> &points, size_t end, const Point &p) {
	Circle c = Circle(p, 0);
	for (size_t i = 0; i < end; i++) {
		const Point &q = points.at(i);
		if (!contains(c, q)) {
			if (c.radius == 0)
				c = makeDiameter(p, q);
			else
				c = makeSmallestEnclosingCircleTwoPoints(points, i + 1, p, q);
		}
	}
	return c;
}



// Two boundary points known
static Circle makeSmallestEnclosingCircleTwoPoints(const vector<Point> &points, size_t end, const Point &p, const Point &q) {
	Circle circ = makeDiameter(p, q);
	Circle left  = Circle(Point(0,0), 0);
	Circle right = Circle(Point(0,0), 0);
	
	// For each point not in the two-point circle
	Point pq = subtract(q, p);
	for (size_t i = 0; i < end; i++) {
		const Point &r = points.at(i);
		if (contains(circ, r))
			continue;
		
		// Form a circumcircle and classify it on left or right side
		double crosss = cross(pq, subtract(r, p));
		Circle c = makeCircumcircle(p, q, r);
		if (c.radius < 0)
			continue;
		else if (crosss > 0 && (left.radius < 0 || cross(pq, subtract(c.center, p)) > cross(pq, subtract(left.center, p))))
			left = c;
		else if (crosss < 0 && (right.radius < 0 || cross(pq, subtract(c.center, p)) < cross(pq, subtract(right.center, p))))
			right = c;
	}
	/*---- omer end ----*/

	/*---- ron start ----*/
	if (left.radius < 0 && right.radius < 0)
		return circ;
	else if (left.radius < 0)
		return right;
	else if (right.radius < 0)
		return left;
	else
		return left.radius <= right.radius ? left : right;
}

/*---- ron end ----*/

/*---- omer start ----*/



































bool Finder(Point p1, Point p2){
	if (p1.x == p2.x && p1.y == p2.y)
	{
		return true;
	}
	return false;
	
}

static Circle finalCircle = Circle(Point(0,0),0);

// http://www.sunshine2k.de/coding/java/Welzl/Welzl.html

void minidisc2(const Point &a, const Point &b, const Point &c){
	// Mathematical algorithm from Wikipedia: Circumscribed circle
		double ox = (min(min(a.x, b.x), c.x) + max(max(a.x, b.x), c.x)) / 2;
		double oy = (min(min(a.y, b.y), c.y) + max(max(a.y, b.y), c.y)) / 2;
		double ax = a.x - ox,  ay = a.y - oy;
		double bx = b.x - ox,  by = b.y - oy;
		double cx = c.x - ox,  cy = c.y - oy;
		double d = (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) * 2;
		if (d == 0){
			finalCircle = Circle(Point(0,0), 0);
			return;
		}
		double x = ((ax*ax + ay*ay) * (by - cy) + (bx*bx + by*by) * (cy - ay) + (cx*cx + cy*cy) * (ay - by)) / d;
		double y = ((ax*ax + ay*ay) * (cx - bx) + (bx*bx + by*by) * (ax - cx) + (cx*cx + cy*cy) * (bx - ax)) / d;
		Point poi = Point(ox + x, oy + y);
		double rad = max(max(distance(poi, a), distance(poi, b)), distance(poi, c));
		
		finalCircle = Circle(poi, rad);
		return;
}


vector<Point> minidisc(vector<Point> p, vector<Point> r){
	if (p.size() == 0 || r.size() == 3)
	{
		minidisc2(r[0],r[1],r[2]);
	}
	else
	{
		Point curP = p.back();
		p.pop_back();
		vector<Point> d = minidisc(p, r);

		
		for (int j = 0; j < d.size(); j++)
		{
			if ((d[j].x == curP.x) && (d[j].y == curP.y))
			{
				return d;
			}
		}

		r.push_back(curP);
		vector<Point> ret = minidisc(p, r);
		return ret;
	}
	return p;
	//makeCircumcircle
}

Circle findMinCircle(Point** points,size_t size){
		
	vector<Point> vecPoint;
	for (int i = 0; i < size; i++)
	{
		vecPoint.push_back(*points[i]);
	}
	
	minidisc(vecPoint, vecPoint);



	//Circle c = makeSmallestEnclosingCircle(vecPoint);
	
	return finalCircle;
	
}

#endif /* MINCIRCLE_H_ */
/*---- omer end ----*/
