import random
import string


class RandomData:

    @staticmethod
    def random_int(start=1, stop=500000):
        random.seed()
        r_id = random.randint(start, stop)
        return r_id

    @staticmethod
    def random_string(length=15):
        return ''.join(random.choices(string.ascii_uppercase + string.ascii_lowercase, k=length))

    @staticmethod
    def random_bool():
        return bool(random.getrandbits(1))
