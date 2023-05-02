from Domain.card_client import CardClient
from Domain.entity import Entity
from Domain.film import Film
from ViewModels.booking_viewmodel import BookingViewModel
from datetime import datetime


class Booking(Entity):
    """
    Descrie o rezervare la film
    """
    def __init__(self, given_film: Film, given_date, given_time, given_card: CardClient, given_id=None):
        """
        Creeaza un obiect de tip rezervare la film
        :param given_film: filmul dat, obiect Film
        :param given_date: data rezervarii, date
        :param given_time: ora rezervarii, time
        :param given_card: cardul clientului ce face rezervarea, obiect CardClient
        :param given_id: id-ul rezervarii
        """
        super(Booking, self).__init__(given_id)
        self.__film = given_film
        self.__card = given_card
        self.__datetime = datetime.combine(given_date, given_time)

    @property
    def film(self):
        return self.__film

    @property
    def card(self):
        return self.__card
        
    @property
    def film_id(self):
        return self.__film.id

    @property
    def card_id(self):
        return self.__card.id

    @property
    def points_increase(self):
        return self.__film.ticket_price//10

    @property
    def date(self):
        return self.__datetime.date()

    @date.setter
    def date(self, value: date):
        self.__datetime = datetime.combine(value, self.__datetime.time())

    @property
    def time(self):
        return self.__datetime.time()

    @time.setter
    def time(self, value: time):
        self.__datetime = datetime.combine(self.__datetime.date(), value)

    @property
    def datetime(self):
        return self.__datetime

    @datetime.setter
    def datetime(self, value: datetime):
        self.__datetime = value

    def __str__(self):
        return str(BookingViewModel(self.id, self.film, self.card, self.date, self.time))
