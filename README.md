# Biblioteki-Projekt-Inzynierski
Biblioteki utworzone w ramach projektu inżynierskiego.
Biblioteki słóżą do sterowania podstawowymi elementami projektów tworzoych na bazie płytek Arduino

Biblioteka Arduino_pin - sterowanie stanami wyjść i odczytem wejść cyfrowych pinów GPIO

Biblioteka Servo_motor_mega/uno -sterowanie modelarskimi silnikami servo (maksymalnie 7) napisane dla płytek mega i uno, 
jedyna różnica pomiędzy bibliotekami to zmiana timera wykorzystywanego do generowania przerwań. 
Do ich poprawnego działania wymagane jest wcześniejsze zainstalowanie biblioteki Arduino_pin

Biblioteka Step_motor - sterowanie silnikami krokowymi za pośrednictwem zewnętrznego układu step stick. pozwala na sterowanie częstotliwością impulsów, 
kierunkiem oraz zadawanie liczby kroków każdemu z silników z osobna. Biblioteka jest przystosowana do obsługi maksymalnie trzech silników krokowych. 
Do jej poprawnego działania wymagane jest wcześniejsze zainstalowanie biblioteki Arduino_pin

Bibliotek Interrupt_pin - biblioteka implementująca przerwania zewnętrzne na płytce Arduino Mega, 
pozwala na przypisanie funkcji obsługujących do każdego z sześciu przerwań zewnętrznych, wybór zdarzenia generującego przerwanie. 
oraz uruchomienie trybu jednokrotnego przerwania. 

Timer - biblioteka implementująca timery odliczające czas co 0.1s 

