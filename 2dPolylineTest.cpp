//
//  2dPolylineTest.cpp
//  
//
//  Created by TuLigen on 16/5/4.
//
//

#include <stdio.h>
#include <vector>
struct Vec2f {
    float x;
    float y;
    Vec2f(){}
    Vec2f(float _x, float _y):x(_x),y(_y){}
    Vec2f normalized(){return Vec2f();}
    float dot(const Vec2f &v)
    {
        return 0.0;
    }
    friend bool  operator==(const Vec2f &left, const Vec2f &right);
    friend Vec2f operator-(const Vec2f &left, const Vec2f &right);
    friend Vec2f operator+(const Vec2f &left, const Vec2f &right);
};

bool operator==(const Vec2f &left, const Vec2f &right)
{
    return true;
}

Vec2f operator-(const Vec2f &left, const Vec2f &right)
{
    return Vec2f(left.x - right.x, left.y - right.y);
}
Vec2f operator+(const Vec2f &left, const Vec2f &right)
{
    return Vec2f(left.x + right.x, left.y + right.y);
}

const float mThickness = 10.0;
typedef  std::vector<Vec2f>  VTXARRAY;
void drawSegment( const Vec2f &p0, const Vec2f &p1, const Vec2f &p2, const Vec2f &p3, VTXARRAY array )
{
    // skip if zero length
    if(p1 == p2) return;
    
    // 1) define the line between the two points
    Vec2f line = (p2 - p1).normalized();
    
    // 2) find the normal vector of this line
    Vec2f normal = Vec2f(-line.y, line.x).normalized();
    
    // 3) find the tangent vector at both the end points:
    //		-if there are no segments before or after this one, use the line itself
    //		-otherwise, add the two normalized lines and average them by normalizing again
    Vec2f tangent1 = (p0 == p1) ? line : ((p1-p0).normalized() + line).normalized();
    Vec2f tangent2 = (p2 == p3) ? line : ((p3-p2).normalized() + line).normalized();
    
    // 4) find the miter line, which is the normal of the tangent
    Vec2f miter1 = Vec2f(-tangent1.y, tangent1.x);
    Vec2f miter2 = Vec2f(-tangent2.y, tangent2.x);
    
    // find length of miter by projecting the miter onto the normal,
    // take the length of the projection, invert it and multiply it by the thickness:
    //		length = thickness * ( 1 / |normal|.|miter| )
    float length1 = mThickness / normal.dot(miter1);
    float length2 = mThickness / normal.dot(miter2);
    
    
    if(true) {
        // set line width to 2
        
        // draw black line between p1 and p2
//        gl::color( Color(0, 0, 0) );
//        gl::drawLine( p1, p2 );
        
        // draw normals in stippled red
        gl::color( Color(1, 0, 0) );
        gl::enable(GL_LINE_STIPPLE);
        gl::drawLine( p1 - normal * mThickness, p1 + normal * mThickness );
        gl::drawLine( p2 - normal * mThickness, p2 + normal * mThickness );
        gl::disable(GL_LINE_STIPPLE);
        
        // draw line segment in stippled gray
        gl::color( Color(0.5f, 0.5f, 0.5f) );
        gl::enable(GL_LINE_STIPPLE);
        gl::drawLine( p1 - normal * mThickness, p2 - normal * mThickness );
        gl::drawLine( p1 + normal * mThickness, p2 + normal * mThickness );
        gl::disable(GL_LINE_STIPPLE);
        
        // draw tangents in gray
        gl::color( Color(0.5f, 0.5f, 0.5f) );
        if(p0 != p1) gl::drawLine( p1 - tangent1 * mThickness, p1 + tangent1 * mThickness );
        if(p2 != p3) gl::drawLine( p2 - tangent2 * mThickness, p2 + tangent2 * mThickness );
        
        // draw miter (normal of tangents) in stippled black
        gl::color( Color(0, 0, 0) );
        gl::enable(GL_LINE_STIPPLE);
        if(p0 != p1) gl::drawLine( p1 - miter1 * length1, p1 + miter1 * length1 );
        if(p2 != p3) gl::drawLine( p2 - miter2 * length2, p2 + miter2 * length2 );
        gl::disable(GL_LINE_STIPPLE);
        
        // draw black circles on miter
        gl::color( Color(0, 0, 0) );
        gl::drawSolidCircle( p1 - length1 * miter1, 0.5f * mRadius );
        gl::drawSolidCircle( p1 + length1 * miter1, 0.5f * mRadius );
        gl::drawSolidCircle( p2 - length2 * miter2, 0.5f * mRadius );
        gl::drawSolidCircle( p2 + length2 * miter2, 0.5f * mRadius );
    }
    
    if(bDrawOutlines) {
        // finally, draw segment in thick black
        glLineWidth(3.0f);
        gl::color( Color::black() );
        gl::drawLine( p1 - length1 * miter1, p2 - length2 * miter2 );
        gl::drawLine( p1 + length1 * miter1, p2 + length2 * miter2 );
        
        // stipple triangles
        gl::enable(GL_LINE_STIPPLE);
        gl::drawLine( p1 - length1 * miter1, p1 + length1 * miter1 );
        gl::drawLine( p1 - length1 * miter1, p2 + length2 * miter2 );
        gl::drawLine( p2 - length2 * miter2, p2 + length2 * miter2 );
        gl::disable(GL_LINE_STIPPLE);
    }
    
}

int main(void)
{
    return 0;
}