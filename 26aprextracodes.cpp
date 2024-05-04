//7

#include <iostream>

using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }

    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }
};

class Triangle : public Shape {
private:
    double side1, side2, side3;

public:
    Triangle(double s1, double s2, double s3) : side1(s1), side2(s2), side3(s3) {}

    double area() const override {
        double s = (side1 + side2 + side3) / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double perimeter() const override {
        return side1 + side2 + side3;
    }
};

int main() {
    Circle circle(5);
    Rectangle rectangle(4, 6);
    Triangle triangle(3, 4, 5);

    cout << "Circle Area: " << circle.area() << ", Perimeter: " << circle.perimeter() << endl;
    cout << "Rectangle Area: " << rectangle.area() << ", Perimeter: " << rectangle.perimeter() << endl;
    cout << "Triangle Area: " << triangle.area() << ", Perimeter: " << triangle.perimeter() << endl;

    return 0;
}


//8
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class PasswordManager {
private:
    unordered_map<string, string> passwords;

public:
    void addPassword(const string& username, const string& password) {
        passwords[username] = password;
    }

    string getPassword(const string& username) const {
        auto it = passwords.find(username);
        if (it != passwords.end()) {
            return it->second;
        } else {
            return "User not found!";
        }
    }
};

int main() {
    PasswordManager manager;
    manager.addPassword("user1", "password1");
    manager.addPassword("user2", "password2");

    cout << "Password for user1: " << manager.getPassword("user1") << endl;
    cout << "Password for user3: " << manager.getPassword("user3") << endl;

    return 0;
}


//9

#include <iostream>

using namespace std;

class WeatherData {
private:
    double temperature;
    double humidity;
    double windSpeed;

public:
    WeatherData(double temp, double hum, double wind) : temperature(temp), humidity(hum), windSpeed(wind) {}

    void updateWeather(double temp, double hum, double wind) {
        temperature = temp;
        humidity = hum;
        windSpeed = wind;
    }

    double getTemperature() const {
        return temperature;
    }

    double getHumidity() const {
        return humidity;
    }

    double getWindSpeed() const {
        return windSpeed;
    }
};

int main() {
    WeatherData station(25.5, 60.0, 10.0);
    cout << "Temperature: " << station.getTemperature() << "°C" << endl;
    cout << "Humidity: " << station.getHumidity() << "%" << endl;
    cout << "Wind Speed: " << station.getWindSpeed() << " km/h" << endl;

    station.updateWeather(27.8, 55.0, 15.5);
    cout << "\nUpdated Weather Data:" << endl;
    cout << "Temperature: " << station.getTemperature() << "°C" << endl;
    cout << "Humidity: " << station.getHumidity() << "%" << endl;
    cout << "Wind Speed: " << station.getWindSpeed() << " km/h" << endl;

    return 0;
}


//10

#include <iostream>
#include <string>

using namespace std;

class Movie {
private:
    string title;
    string genre;
    int releaseYear;
    bool available;

public:
    Movie(const string& t, const string& g, int year) : title(t), genre(g), releaseYear(year), available(true) {}

    const string& getTitle() const {
        return title;
    }

    const string& getGenre() const {
        return genre;
    }

    int getReleaseYear() const {
        return releaseYear;
    }

    bool isAvailable() const {
        return available;
    }

    void rentMovie() {
        if (available) {
            available = false;
            cout << "Movie " << title << " rented successfully!" << endl;
        } else {
            cout << "Movie " << title << " is not available for rent." << endl;
        }
    }

    void returnMovie() {
        if (!available) {
            available = true;
            cout << "Movie " << title << " returned successfully!" << endl;
        } else {
            cout << "Movie " << title << " is already available." << endl;
        }
    }
};

int main() {
    Movie movie1("Inception", "Sci-Fi", 2010);
    Movie movie2("The Godfather", "Crime", 1972);

    movie1.rentMovie();
    movie1.returnMovie();
    movie2.rentMovie();
    movie1.rentMovie();

    return 0;
}




