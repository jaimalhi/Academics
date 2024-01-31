package cmpt213.as1;
import java.util.Objects;

/**
 * @author Jai Malhi
 * @owner stores name of the bike owner
 * @serialNum stores the serial number of the bike
 * @bikeType stores the type of the bike
 * @brakeType stores the type of brakes on the bike
 * @wheelSize stores the size of the wheels in inches
 * @bikeID the ID that is assigned to all bikes within the registry
 * */
public class BikeRegistry {
    String owner;
    String serialNum;
    String bikeType;
    String brakeType;
    int wheelSize;
    int bikeID;

    //constructor
    public BikeRegistry(String owner, String serialNum, String bikeType, String brakeType, int wheelSize, int bikeID){
        this.owner = owner;
        this.serialNum = serialNum;
        this.bikeType = bikeType;
        this.brakeType = brakeType;
        this.wheelSize = wheelSize;
        this.bikeID = bikeID;
    }

    @Override
    public String toString() {
        return getClass().getName() + "{ID: " + this.bikeID + ", Owner: " + this.owner + ", Type: " + this.bikeType + ", Serial #: "
                + this.serialNum + ", Brake: " + this.brakeType + ", Wheel-Size: " + this.wheelSize + " }";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        BikeRegistry that = (BikeRegistry) o;
        return wheelSize == that.wheelSize && bikeID == that.bikeID && Objects.equals(owner, that.owner) && Objects.equals(serialNum, that.serialNum) && Objects.equals(bikeType, that.bikeType) && Objects.equals(brakeType, that.brakeType);
    }

    @Override
    public int hashCode() {
        return Objects.hash(owner, serialNum, bikeType, brakeType, wheelSize, bikeID);
    }

    public void setOwner(String owner){ this.owner = owner; }
    public void setSerialNum(String serialNum){ this.serialNum = serialNum; }
    public void setBikeType(String bikeType){ this.bikeType = bikeType; }
    public void setBrakeType(String brakeType){ this.brakeType = brakeType; }
    public void setWheelSize(int wheelSize){ this.wheelSize = wheelSize; }
    public void setBikeID(int bikeID){ this.bikeID = bikeID; }
    public int getBikeID(){ return this.bikeID; }
}
