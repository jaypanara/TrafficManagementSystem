"""https://www.geeksforgeeks.org/program-check-three-points-collinear/
https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
https://git.uwaterloo.ca/ece650-f2021/python-examples
https://www.w3schools.com/"""

import re
import sys

inp = ["add", "rm", "mod", "gg"]


class Point(object):
    def __init__(self, x, y):
        self.x = (x)
        self.y = (y)

    def __str__(self):
        return '(' + str(self.x) + ',' + str(self.y) + ')'


class Line(object):
    def __init__(self, src, dst):
        self.src = src
        self.dst = dst

    def __str__(self):
        return str(self.src) + '-->' + str(self.dst)


def find_intersection(p1, p2, q1, q2):
    orientation1 = get_orientation(p1, p2, q1)
    orientation2 = get_orientation(p1, p2, q2)
    orientation3 = get_orientation(q1, q2, p1)
    orientation4 = get_orientation(q1, q2, p2)

    if (orientation1 != orientation2) & (orientation3 != orientation4):
        return True
    else:
        return False


def get_orientation(p, q, r):
    # Calculating determinant of vectors PQ and QR
    det = float(((q[0] - p[0]) * (r[1] - q[1])) - ((r[0] - q[0]) * (q[1] - p[1])))
    if (det < 0):
        return 1
    elif (det > 0):
        return 2
    else:
        return 0


class Streets():
    def __init__(self):
        self.dict = {}

    def add(self, name, coordinates):
        self.dict[name] = coordinates
        # print(self.dict)
        return self.dict

    def mod(self, name, coordinates):
        if name in self.dict:
            self.dict[name] = coordinates
            # print(self.dict)
            return dict
        else:
            raise Exception("Error: Street Name not present")

    def rm(self, name):
        if name in self.dict:
            del self.dict[name]
            # print(self.dict)
            return dict
        else:
            raise Exception("Error: Wrong street name or missing from the list")
    def gg(self):
        dict1 = {}

        lst_vertices = []
        global vertices
        vertices = []
        # print(len(dict))
        for k, v in self.dict.items():

            for i in range(len(v) - 1):
                p1 = v[i]
                p2 = v[i + 1]
                for p, s in self.dict.items():
                    if (p == k):
                        continue
                    else:
                        for j in range(len(s) - 1):
                            q1 = s[j]
                            q2 = s[j + 1]
                            # print(p1,p2,q1,q2)
                            point1 = Point(p1[0], p1[1])
                            point2 = Point(p2[0], p2[1])
                            point3 = Point(q1[0], q1[1])
                            point4 = Point(q2[0], q2[1])
                            if find_intersection((p1[0], p1[1]), (p2[0], p2[1]), (q1[0], q1[1]), (q2[0], q2[1])):
                                l1 = Line(point1, point2)
                                l2 = Line(point3, point4)
                                # print(l1,l2)
                                lst_vertices.append((p1[0], p1[1]))
                                lst_vertices.append((p2[0], p2[1]))
                                lst_vertices.append((q1[0], q1[1]))
                                lst_vertices.append((q2[0], q2[1]))
                                # print('Intersect of', l1, 'with', l2, 'is', intersect(l1, l2))
                                intersect(l1, l2)

        # print("The intersection vertices are : ", (list(set(vertices))))

        temp = []
        temp_dict = {}
        for i in lst_vertices:
            if i not in temp:
                temp.append(i)
        # print(temp)

        for i in vertices:
            if i not in temp:
                temp.append(i)

        all_vertices = (temp)
        # print(all_vertices)
        for i in range(len(all_vertices)):
            temp_dict[i + 1] = all_vertices[i]
        print("V = {")
        for a, b in temp_dict.items():  # CONTAINS ALL THE VERTICES WITH SERIAL NUMBERS
            print('  {0}: ({1:.2f},{2:.2f})'.format((a), (b[0]), (b[1])))
            # print("Hi b here",b)
        print("}")

        h = list(self.dict.values())
        a = list(temp_dict.values())
        z = list(set(vertices))
        # lst_intersection = []  # collecting the intersection points
        distance = []
        # distance_last = []
        lst_edges = []
        global x1, x2, y1, y2, x3, y3
        for i in range(len(h)):
            # count = 0
            # lst_intersection=[]
            # print("H[i] ",h[i])
            for j in range(len(h[i]) - 1):
                count = 0
                lst_intersection = []
                # print(len(h[i])-1)
                for k in range(len(z)):
                    x1 = h[i][j][0]
                    y1 = h[i][j][1]
                    x2 = h[i][j + 1][0]
                    y2 = h[i][j + 1][1]
                    x3 = z[k][0]
                    y3 = z[k][1]
                    # print(x1, y1, x2, y2, x3, y3)
                    if ((x1 == x3 and y1 == y3) or (x2 == x3 and y2 == y3)):
                        lst_edges.append(((x1, y1), (x2, y2)))
                        continue

                    b = int((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2)))
                    # b =round(b,2)
                    if (b == 0):
                        count = count + 1
                        # print("collinear")
                        lst_intersection.append((x3, y3))  # list which contains all the intersecting points
                        # print("List intersecection is ",lst_intersection)
                    else:
                        continue
                if count == 1:
                    # count = 0
                    for w in range(len(z)):
                        x1 = h[i][j][0]
                        y1 = h[i][j][1]
                        x2 = h[i][j + 1][0]
                        y2 = h[i][j + 1][1]
                        x3 = z[w][0]
                        y3 = z[w][1]
                        # print(x1, y1, x2, y2, x3, y3)
                        if ((x1 == x3 and y1 == y3) or (x2 == x3 and y2 == y3)):
                            lst_edges.append(((x1, y1), (x2, y2)))
                            continue

                        c = int(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2))
                        if c == 0:
                            # print((x1, y1), " and ", (x3, y3), " are one edge and ", (x2, y2), " and ", (x3, y3),"are another edge")
                            lst_edges.append(((x1, y1), (x3, y3)))
                            lst_edges.append(((x2, y2), (x3, y3)))
                elif count > 1:
                    global X, Y
                    lst_intersection = list(set(lst_intersection))
                    distance = []
                    lst_intersection1 = []
                    for l in range(len(lst_intersection)):
                        X = lst_intersection[l][0]
                        Y = lst_intersection[l][1]
                        b = int((x1 * (y2 - Y)) + (x2 * (Y - y1)) + (X * (y1 - y2)))
                        if b == 0:
                            lst_intersection1.append((X, Y))
                    lst_intersection = lst_intersection1.copy()
                    while (len(lst_intersection) != 1):
                        distance = []
                        for m in range(len(lst_intersection)):
                            X = lst_intersection[m][0]
                            Y = lst_intersection[m][1]
                            # b = int((x1 * (y2 - Y)) + (x2 * (Y - y1)) + (X * (y1 - y2)))
                            dis = ((((x1 - X) ** 2) + ((y1 - Y) ** 2)) ** 0.5)
                            # if dis!=0:
                            distance.append(dis)
                            # else:
                            #   continue
                        # e = min(list(enumerate(distance)))
                        e = min(distance)
                        # global o
                        # for k in range(len(lst_intersection)):                                      #removing points which are vertices as well like (5,8) (5,8) cannot be an edge
                        #     X = lst_intersection[k][0]
                        #     Y = lst_intersection[k][1]
                        #     b = int((x1 * (y2 - Y)) + (x2 * (Y - y1)) + (X * (y1 - y2)))
                        # dis = ((((x1 - X) ** 2) + ((y1 - Y) ** 2)) ** 0.5)
                        # if dis==e:
                        #     o=k

                        e1 = distance.index(e)
                        # e1 = e[0]

                        # print((lst_intersection[e1][0], lst_intersection[e1][1]), "and ", (x1, y1), "Form the edge")
                        lst_edges.append(((lst_intersection[e1][0], lst_intersection[e1][1]), (x1, y1)))

                        x1 = lst_intersection[e1][0]

                        y1 = lst_intersection[e1][1]

                        r = (lst_intersection[e1][0], lst_intersection[e1][1])

                        lst_intersection.remove(r)
                    if len(lst_intersection) == 1:
                        lst_edges.append(((x1, y1), (lst_intersection[0][0], lst_intersection[0][1])))

                        x1 = lst_intersection[0][0]
                        y1 = lst_intersection[0][1]
                        r = ((lst_intersection[0][0], lst_intersection[0][1]))
                        lst_intersection.remove(r)
                    if len(lst_intersection) == 0:
                        lst_edges.append(((x1, y1), (x2, y2)))

        # print(lst_edges)  # contains all the edges pair
        a = []
        p = []
        a1 = list(set(lst_edges))
        # print(a1)
        lst_edges1 = a1.copy()
        for i in range(len(a1)):
            X1 = a1[i][0][0]

            Y1 = a1[i][0][1]
            X2 = a1[i][1][0]
            Y2 = a1[i][1][1]
            # print("hELLO",X1,Y1,X2,Y2)
            count = 0
            for k in range(len(z)):
                X3 = z[k][0]
                Y3 = z[k][1]
                g = round((((X1 - X2) ** 2 + ((Y1 - Y2) ** 2)) ** 0.5), 3)
                h = round((((X1 - X3) ** 2 + ((Y1 - Y3) ** 2)) ** 0.5), 3)
                i = round(((((X3 - X2) ** 2) + ((Y3 - Y2) ** 2)) ** 0.5), 3)
                if (X1 == X3 and Y1 == Y3) or (X2 == X3 and Y2 == Y3):
                    continue
                if (g == h + i):
                    count = count + 1
                    # r=((X1,Y1),(X2,Y2))
                    # lst_edges1.remove(r)

            if count > 0:
                lst_edges1.remove(((X1, Y1), (X2, Y2)))

        a2 = lst_edges1.copy()
        # print("a2 ",a2)
        a4 = []
        for coor_pair in a2:
            a4.append(frozenset(coor_pair))  # Removing one of the coordinates like [((1,2)(3,4))((3,4)(1,2))]

        a4 = set(a4)
        # print("a4",a4)
        a5 = []
        for coor_pair in list(a4):
            a5.append(tuple(coor_pair))
        # print("a5",a5)
        a2 = a5.copy()
        b = list(temp_dict.keys())
        c = list(temp_dict.values())
        for i in range(len(a2)):
            if (a2[i][0] != a2[i][1]):
                a.append(a2[i])
        # print(a)

        for i in range(len(a)):
            for j in range(len(c)):
                if a[i][0] == c[j] or a[i][1] == c[j]:
                    p.append(b[j])
                    # print("Hi",p)

        print("E = {")
        for i in range(0, len(p) - 1, 2):
            if i!=len(p)-2:
                print("  <" + str(p[i]) + "," + str(p[i + 1]) + ">,")
            else:
                print("  <" + str(p[i]) + "," + str(p[i + 1]) + ">")
        print("}")

        return (temp_dict, lst_edges)


def intersect(l1, l2):
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y
    # print(x1,y1,x2,y2,x3,y3,x4,y4)
    try:
        xnumerator = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4))
        xdenominator = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))

        xcoordinate = xnumerator / xdenominator
        xcoordinate = round(xcoordinate, 2)

        ynumerator = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)
        ydenominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)

        ycoordinate = ynumerator / ydenominator
        ycoordinate = round(ycoordinate, 2)
        vertices.append((xcoordinate, ycoordinate))
        # print(vertices)
        return Point(xcoordinate, ycoordinate)
    except ZeroDivisionError:
        # print(l1, l2)
        pass


temp_street_names = []


def input_check(x):
    count = 0
    command, street_name, coordinates = None, None, None
    # global temp_street_names
    # temp_street_names = []
    if (y[0] in inp):

        if y[0] == 'add':
            command = 'add'

            if (len(re.findall(r'\"', x)) == 2):  # checking the quotes
                temp = 0
                temp1 = 0
                for i in x:
                    if i == "(":
                        temp += 1
                        temp1 += 1
                    elif i == ")":
                        temp -= 1
                        temp1 += 1
                if temp < 0 or temp > 0:
                    raise Exception("Error incorrect number of brackets")
                if temp1 == 0:
                    raise Exception("Error: No brackets")

                if len(re.findall(r' "[a-zA-Z ]+" ', x)) == 1:  # checking spacing
                    if re.findall(r'\" (.+?) \"', x) or re.findall(r'\" (.+?)\"', x) or re.findall(r'\"(.+?) \"', x):
                        raise Exception("Error: There is a leading or a trailing whitespace")
                    else:
                        street_name = re.findall(r'\"(.+?)\"', x)
                    if len(re.findall(r'[a-zA-Z][ ]{1}\"', x)) == 0:
                        raise Exception("Error: There is more than one white space between command and the street name")
                    if (len(re.findall(r'\"[a-zA-z ]+[ ]{2,}[a-zA-z ]+\"', x)) > 0):
                        raise Exception("Error: There exists more than one space between the street name")
                    if (len(re.findall(r'\"[ ]\(',x))==0):
                        raise Exception("Error: There is more than one whitespace between the street name and the cooridnates")
                    if (street_name[0].isspace() == True):
                        raise Exception("Error: Street name contains only whitespaces")
                    street_name[0] = street_name[0].lower()
                    for i in range(len(temp_street_names)):
                        if street_name[0] == temp_street_names[i]:
                            raise Exception("Error: Street name already used")
                    if len(re.findall(r'\((-?[0-9]+,-?[0-9]+)\)', x)) == len(re.findall(r'\((.+?)\)', x)):
                        j = re.findall(r'\((.+?)\)', x)  # coordinates
                    else:
                        raise Exception("Error: More space between the numbers in the coordinates or '+' in the coordinates")
                    if len(re.findall(r'\)\(', x)) > 0 or len(re.findall(r'\"\(', x)) > 0:
                        raise Exception('Error: No space between " and ( or no space between ) and (')
                    if len(re.findall(r'\)[ ]{2,}\(',x))>0:
                        raise Exception("Error: More than one white space between the coordinates")
                    # temp_street_names.append(street_name[0])
                    coordinates = [eval(x) for x in j]
                    # print(coordinates)
                    coordinates1 = list(set(coordinates))
                    if len(coordinates) != len(coordinates1):
                        raise Exception("Error: Repeated Coordinates")
                    # print(j)
                    # print(coordinates)
                    if len(coordinates) < 2:
                        raise Exception("Error: Less number of coordinates for forming a road")
                    temp_street_names.append(street_name[0])
                else:
                    raise Exception("Error: Incorrect spacing or street name containing numbers or special characters")

            else:
                raise Exception("Error: Incorrect number of quotes")
        elif y[0] == 'mod':
            command = 'mod'
            if (len(re.findall(r'\"', x)) == 2):  # checking quotes
                temp = 0
                for i in x:
                    if i == "(":
                        temp += 1
                    elif i == ")":
                        temp -= 1
                if count < 0 or count > 0:
                    raise Exception("Error incorrect number of brackets")
                if len(re.findall(r' "[a-z,A-Z ]+" ', x)) == 1:
                    if re.findall(r'\" (.+?) \"', x) or re.findall(r'\" (.+?)\"', x) or re.findall(r'\"(.+?) \"', x):
                        raise Exception("Error: There is a leading or a trailing whitespace")
                    else:
                        street_name = re.findall(r'\"(.+?)\"', x)

                    if len(re.findall(r'[a-zA-Z][ ]{1}\"', x)) == 0:
                        raise Exception("Error: There is more than one white space between command and the street name")

                    if (len(re.findall(r'\"[a-zA-z ]+[ ]{2,}[a-zA-z ]+\"', x)) > 0):
                        raise Exception("Error: There exists more than one space between the street name")
                    if (len(re.findall(r'\"[ ]\(',x))==0):
                        raise Exception("Error: There is more than one whitespace between the street name and the cooridnates")

                    if (street_name[0].isspace() == True):
                        raise Exception("Error: Street name contains only whitespaces")
                    street_name[0] = street_name[0].lower()
                    if len(re.findall(r'\((-?[0-9]+,-?[0-9]+)\)', x)) == len(re.findall(r'\((.+?)\)', x)):
                        j = re.findall(r'\((.+?)\)', x)  # coordinates
                    else:
                        raise Exception("Error: More space between the numbers in the coordinates or '+' in the coordinates")
                    if len(re.findall(r'\)\(', x)) > 0 or len(re.findall(r'\"\(', x)) > 0:
                        raise Exception('Error: No space between " and ( or no space between ) and (')
                    if len(re.findall(r'\)[ ]{2,}\(',x))>0:
                        raise Exception("Error: More than one white space between the coordinates")

                    coordinates = [eval(x) for x in j]
                    coordinates1 = list(set(coordinates))
                    if len(coordinates) != len(coordinates1):
                        raise Exception("Error: Repeated Coordinates")
                    # print(j)
                    #print(coordinates)
                    if len(coordinates) < 2:
                        raise Exception("Error: Less number of coordinates for forming a road")
                else:
                    raise Exception("Error: Incorrect spacing")
            else:
                raise Exception("Error: Incorrect number of quotes")
        elif y[0] == 'rm':
            command = 'rm'
            if (len(re.findall(r'\"', x)) == 2):
                if (len(re.findall(r'\((.+?)\)', x)) == 0):
                    if len(re.findall(r'\" (.+?) \"', x))>0 or len(re.findall(r'\" (.+?)\"', x))>0 or len(re.findall(r'\"(.+?) \"', x))>0:
                        raise Exception("Error: There is a leading or a trailing whitespace")
                    else:
                        street_name = re.findall(r'\"(.+?)\"', x)
                    if (street_name[0].isspace() == True):
                        raise Exception("Error: Street name contains only whitespaces")
                    if len(re.findall(r'[a-zA-Z][ ]{1}\"', x)) == 0:
                        raise Exception("Error: There is more than one white space between command and the street name")
                    if (len(re.findall(r'\"[a-zA-z ]+[ ]{2,}[a-zA-z ]+\"', x)) > 0):
                        raise Exception("Error: There exists more than one space between the street name")
                    # street_name = re.findall(r'\"(.+?)\"', x)
                    street_name[0] = street_name[0].lower()
                    if street_name[0] in temp_street_names:
                        temp_street_names.remove(street_name[0])
                    else:
                        raise Exception("Error: Street name is not added previously")
                else:
                    raise Exception("Error: Wrong inputs for remove")
                # print(street_name)
            else:
                raise Exception("Error: Incorrect number of quotes")
        elif y[0] == 'gg':
            if len(y) > 1:
                raise Exception("Error: Incorrect input for gg")
            else:
                command = 'gg'



    else:
        raise Exception("Error: Incorrect input")

    return command, street_name, coordinates


# def input_check_with_g():
# YOUR CODE GOES HERE


def main():
    # YOUR MAIN CODE GOES HERE
    Dog = Streets()
    global cmd, sn, coor, y
    while True:
        try:
            x = input()
            y = x.split()
            # print(y)

            if x == "":
                break
            # print("read a line:", x)

            cmd, sn, coor = input_check(x)
            # print(cmd, sn, coor)
            if cmd == 'add':
                # sn, coor = input_check(x)
                Dog.add(sn[0], coor)
            elif cmd == 'mod':
                # sn, coor = input_check(x)
                Dog.mod(sn[0], coor)
            elif cmd == 'rm':
                Dog.rm(sn[0])
            elif cmd == 'gg':
                n, m = Dog.gg()
        except EOFError:
            #print("EOF detected. Exiting program")
            break
        except Exception as e:
            print(e)
        #except KeyboardInterrupt:
            #   print("[Error]Keyboard Interrupt, press 'ENTER' or 'CTRL+D' to exit.")
            #break
    #print("Finished reading input")
    # return exit code 0 on successful termination
    sys.exit(0)


if __name__ == "__main__":
    main()

# add "Weber street" (2,-1) (2,2) (5,5) (5,6) (3,8)
# add "King" (4,2) (4,8)
# add "Devon" (1,4) (5,8)
# add "Weber" (2,2)(6,2)(7,5)(10,9)
# add "King" (10,4)(6,8)(12,4)
# add "King" (5,2) (5,8)
# add "Weber" (0,0) (1,1) (2,2) (3,3) (4,4) (5,5)
# add "King" (2,0) (0,2)
# add "Devon" (2,0) (2,4)
