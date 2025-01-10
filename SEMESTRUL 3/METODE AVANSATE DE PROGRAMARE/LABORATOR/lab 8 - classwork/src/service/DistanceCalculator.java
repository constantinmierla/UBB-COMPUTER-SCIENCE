package service;

import domain.GPSCoordinates;

public interface DistanceCalculator {
	
	Double computeDistance(GPSCoordinates point1,GPSCoordinates point2);
}
