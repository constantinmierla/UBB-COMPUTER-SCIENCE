package service;

import domain.GPSCoordinates;
public class EuclideanDistanceCalculator implements DistanceCalculator{

	@Override
	public Double computeDistance(GPSCoordinates point1, GPSCoordinates point2) {
		// TODO implement euclidean distance computation between two points
		double x = point1.getLatitude() - point2.getLatitude();
		double y = point1.getLongitude() - point2.getLongitude();
		return Math.sqrt(x*x + y*y);
	}

}
