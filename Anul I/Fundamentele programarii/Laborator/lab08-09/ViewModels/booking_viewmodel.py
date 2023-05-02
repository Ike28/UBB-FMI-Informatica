from datetime import date, time


class BookingViewModel:
    def __init__(self, given_id, given_film, given_card, given_date: date, given_time: time):
        self.id = given_id
        self.film = given_film
        self.card = given_card
        self.date = given_date
        self.time = given_time

    def __str__(self):
        if self.card is None:
            return f'ID: {self.id}\n---> Rezervare la {self.film}\n- rezervare in data de {self.date} la ora {self.time}'
        else:
            return f'ID: {self.id}\n---> Rezervare la {self.film}\n---> facuta de clientul cu cardul {self.card}\n* rezervat pentru {self.date.strftime("%A %#d %b %Y")} la ora {self.time.strftime("%H:%M")}'
