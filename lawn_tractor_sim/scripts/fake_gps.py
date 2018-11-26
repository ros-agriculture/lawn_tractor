#! /usr/bin/python

from geographiclib.geodesic import Geodesic
import math
import pyproj
geod = Geodesic.WGS84


from pyproj import Proj, transform

inProj = Proj(init='epsg:3857')
outProj = Proj(init='epsg:4326')
x1,y1 = -11705274.6374,4826473.6922
x2,y2 = transform(inProj,outProj,x1,y1)
print x2,y2


g = geod.Inverse(-41.32, 174.81, 40.96, -5.50)
print "the distance is {:.3f} m.".format(g['s12'])

# Paris
lat0 = 48 + 50/60.0 
lon0 = 2 + 20/60.0

# Sample forward calculation
lat = 50.9
lon = 1.8
h = 0

x = 0.0
y = 0.0
z = 0.0




# g = geod.Forward(lat, lon, h, x, y, z)
print (x)
