#include <QCoreApplication>

//my first program in C++
#include <iostream>

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// ---------------------------------- OSU CODE ----------------------------------
// -----------------------------------vvvvvvvv-----------------------------------
// ------------------------------------------------------------------------------
#include <math.h>
void gen_tornado( int xs, int ys, int zs, int time, float *tornado )
/*
 *  Gen_Tornado creates a vector field of dimension [xs,ys,zs,3] from
 *  a proceedural function. By passing in different time arguements,
 *  a slightly different and rotating field is created.
 *
 *  The magnitude of the vector field is highest at some funnel shape
 *  and values range from 0.0 to around 0.4 (I think).
 *
 *  I just wrote these comments, 8 years after I wrote the function.
 *
 * Developed by Roger A. Crawfis, The Ohio State University
 *
 */
{
    float x, y, z;
    int ix, iy, iz;
    float r, xc, yc, scale, temp, z0;
    float r2 = 8;
    float SMALL = 0.00000000001;
    float xdelta = 1.0 / (xs-1.0);
    float ydelta = 1.0 / (ys-1.0);
    float zdelta = 1.0 / (zs-1.0);

    for( iz = 0; iz < zs; iz++ )
    {
        z = iz * zdelta;                        // map z to 0->1
        xc = 0.5 + 0.1*sin(0.04*time+10.0*z);   // For each z-slice, determine the spiral circle.
        yc = 0.5 + 0.1*cos(0.03*time+3.0*z);    //    (xc,yc) determine the center of the circle.
        r = 0.1 + 0.4 * z*z + 0.1 * z * sin(8.0*z); //  The radius also changes at each z-slice.
        r2 = 0.2 + 0.1*z;                           //    r is the center radius, r2 is for damping
        for( iy = 0; iy < ys; iy++ )
        {
            y = iy * ydelta;
            for( ix = 0; ix < xs; ix++ )
            {
                x = ix * xdelta;
                temp = sqrt( (y-yc)*(y-yc) + (x-xc)*(x-xc) );
                scale = fabs( r - temp );
                /*
 *  I do not like this next line. It produces a discontinuity
 *  in the magnitude. Fix it later.
 *
 */
                if ( scale > r2 )
                    scale = 0.8 - scale;
                else
                    scale = 1.0;
                z0 = 0.1 * (0.1 - temp*z );
                if ( z0 < 0.0 )  z0 = 0.0;
                temp = sqrt( temp*temp + z0*z0 );
                scale = (r + r2 - temp) * scale / (temp + SMALL);
                scale = scale / (1+z);
                *tornado++ = scale * (y-yc) + 0.1*(x-xc);
                *tornado++ = scale * -(x-xc) + 0.1*(y-yc);
                *tornado++ = scale * z0;
            }
        }
    }
}
// ------------------------------------------------------------------------------
// -----------------------------------^^^^^^^^-----------------------------------
// ---------------------------------- OSU CODE ----------------------------------
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

class FlowDataSource {
private:
    float* cartesianDataGrid;
    int cartesianDataGridSize;
    int xs;
    int ys;
    int zs;
    bool gridInitialized;
public:
    // Constructor
    // TODO add init cartesianDataGrid parameter
    FlowDataSource(int xs=0, int ys=0, int zs=0) {
        cartesianDataGridSize = 3*xs*ys*zs;
        gridInitialized = false;
        this->xs = xs;
        this->ys = ys;
        this->zs = zs;
    }
    void createData(int xs, int ys, int zs, int time=0){
        // fill cartesianDataGrid with data
        // TODO: potentially add start indices for tornado with tornadoX, tornadoY, tornadoZ, and custom tornado size with tornadoXS
        std::cout << "called createData\n";

        cartesianDataGridSize = xs*ys*zs;
        if (gridInitialized) {
            //TODO
            std::cout << "WARNING unimplemented: gridInitialized!\n";
        } else {
            cartesianDataGrid = new float[cartesianDataGridSize]();
            gen_tornado(xs, ys, zs, time, cartesianDataGrid);
        }
    }
    // tornado index forumla for spacial coordinate (x y z) (order: x rows nested in y rows nested in z rows
    // xIndex = 3*(x + y*xs + z*ys*xs) mit yIndex=xIndex+1 und zIndex=xIndex+2
    // Currently: Assuming iz,iy,ix are already flat indices
    float getDataValue(int iz, int iy, int ix, int ic){
        // return wind value of grid position (iz,iy,ix) for vector component ic
    }
    void printValuesOfHorizontalSlice(int iz, int ic){
        int startIndex = 3*xs*ys*iz;
        int stopIndex = startIndex+3*xs*ys;
        int i = startIndex+ic;
        while (i<stopIndex) {
            std::cout << cartesianDataGrid[i];
            i += 3;
        }
    }
};

int main()
{
    std::cout << "Hello World";
}
