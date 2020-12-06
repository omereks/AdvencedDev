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
Circle findMinCircle(Point** points,size_t size){
	
	return Circle(Point(0,0),0);
}

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
	Circle c = Circle::INVALID;
	for (size_t i = 0; i < shuffled.size(); i++) {
		const Point &p = shuffled.at(i);
		if (c.r < 0 || !c.contains(p))
			c = makeSmallestEnclosingCircleOnePoint(shuffled, i + 1, p);
	}
	return c;
}

/*---- omer end ----*/

/*---- ron start ----*/

// One boundary point known
static Circle makeSmallestEnclosingCircleOnePoint(const vector<Point> &points, size_t end, const Point &p) {
	Circle c{p, 0};
	for (size_t i = 0; i < end; i++) {
		const Point &q = points.at(i);
		if (!c.contains(q)) {
			if (c.r == 0)
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
	Circle left  = Circle::INVALID;
	Circle right = Circle::INVALID;
	
	// For each point not in the two-point circle
	Point pq = q.subtract(p);
	for (size_t i = 0; i < end; i++) {
		const Point &r = points.at(i);
		if (circ.contains(r))
			continue;
		
		// Form a circumcircle and classify it on left or right side
		double cross = pq.cross(r.subtract(p));
		Circle c = makeCircumcircle(p, q, r);
		if (c.r < 0)
			continue;
		else if (cross > 0 && (left.r < 0 || pq.cross(c.c.subtract(p)) > pq.cross(left.c.subtract(p))))
			left = c;
		else if (cross < 0 && (right.r < 0 || pq.cross(c.c.subtract(p)) < pq.cross(right.c.subtract(p))))
			right = c;
	}
	
	// Select which circle to return
	if (left.r < 0 && right.r < 0)
		return circ;
	else if (left.r < 0)
		return right;
	else if (right.r < 0)
		return left;
	else
		return left.r <= right.r ? left : right;
}

/*---- ron end ----*/

/*---- omer start ----*/


Circle makeDiameter(const Point &a, const Point &b) {
	Point c{(a.x + b.x) / 2, (a.y + b.y) / 2};
	return Circle{c, max(distance(c, a), distance(c, b))};
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
	Point p{ox + x, oy + y};
	double r = max(max(distance(p, a), distance(p, b)), distance(p, c));
	return Circle{p, r};
}
#endif /* MINCIRCLE_H_ */
/*---- omer end ----*/
