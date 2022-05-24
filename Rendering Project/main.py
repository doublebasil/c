import math

def regular(polygonSides):
    if polygonSides < 3:
        print("Not enough sides")
        exit()
    # Initialise variables
    vertices = []
    # --- Create a single side which the rest of the cube will be based on
    # Create first point at 0,0,0
    vertices.append([0, 0, 0])
    # Create the rest of this side within z=0 plane
    interiorAngle = 180 - (360 / polygonSides)

    print(interiorAngle)
    


# def createFile():
#     pass

def main():
    # regular(5)

    for i in range(3, 7):
        print(str(i) + " -> " + str(180 - (360 / i)))

if __name__ == '__main__':
    main()