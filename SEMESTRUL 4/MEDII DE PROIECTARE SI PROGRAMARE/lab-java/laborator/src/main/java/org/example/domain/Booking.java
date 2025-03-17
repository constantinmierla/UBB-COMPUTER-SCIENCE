package org.example.domain;

import java.util.List;
import java.util.Objects;

public class Ticket extends Entity<Long> {
    private Long flightId;
    private List<Integer> seatNumbers;
    private List<String> touristNames;

    public Ticket(Long flightId, List<Integer> seatNumbers, List<String> touristNames) {
        this.flightId = flightId;
        this.seatNumbers = seatNumbers;
        this.touristNames = touristNames;
    }

    public Long getFlightId() {
        return flightId;
    }

    public void setFlightId(Long flightId) {
        this.flightId = flightId;
    }

    public List<Integer> getSeatNumbers() {
        return seatNumbers;
    }

    public void setSeatNumbers(List<Integer> seatNumbers) {
        this.seatNumbers = seatNumbers;
    }

    public List<String> getTouristNames() {
        return touristNames;
    }

    public void setTouristNames(List<String> touristNames) {
        this.touristNames = touristNames;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Ticket that)) return false;
        return Objects.equals(flightId, that.flightId) &&
                Objects.equals(seatNumbers, that.seatNumbers) &&
                Objects.equals(touristNames, that.touristNames);
    }

    @Override
    public int hashCode() {
        return Objects.hash(flightId, seatNumbers, touristNames);
    }
}
