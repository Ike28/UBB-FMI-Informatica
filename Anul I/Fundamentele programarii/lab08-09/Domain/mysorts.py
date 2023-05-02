from copy import deepcopy


class MySorts:
    @staticmethod
    def __my_partition(iterable, start_position, end_position, key=lambda x: x):
        pos_of_lowest = start_position
        pivot_pos = end_position
        for each in range(start_position, end_position):
            if key(iterable[each]) <= key(iterable[pivot_pos]):
                iterable[pos_of_lowest], iterable[each] = iterable[each], iterable[pos_of_lowest]
                pos_of_lowest += 1
        iterable[pos_of_lowest], iterable[pivot_pos] = iterable[pivot_pos], iterable[pos_of_lowest]
        return pos_of_lowest

    @staticmethod
    def __my_quicksort(thing_to_sort, start, end, key1=lambda x: x, reverse=False):

        if len(thing_to_sort) == 1:
            return thing_to_sort
        if start < end:
            if reverse is False:
                part_index = MySorts.__my_partition(thing_to_sort, start, end, key1)
            else:
                part_index = MySorts.__my_partition(thing_to_sort, start, end, key=lambda x: -key1(x))
            MySorts.__my_quicksort(thing_to_sort, start, part_index-1, key1, reverse)
            MySorts.__my_quicksort(thing_to_sort, part_index+1, end, key1, reverse)

    @staticmethod
    def __my_mergesort(thing_to_sort, key=lambda x: x, reverse=False):
        if len(thing_to_sort) > 1:
            middle_pos = len(thing_to_sort)//2
            left = thing_to_sort[:middle_pos]
            right = thing_to_sort[middle_pos:]
            MySorts.__my_mergesort(left, key, reverse)
            MySorts.__my_mergesort(right, key, reverse)
            left_index, right_index, sorted_index = 0, 0, 0
            while left_index < len(left) and right_index < len(right):
                if reverse is False:
                    if key(left[left_index]) < key(right[right_index]):
                        thing_to_sort[sorted_index] = left[left_index]
                        left_index += 1
                    else:
                        thing_to_sort[sorted_index] = right[right_index]
                        right_index += 1
                else:
                    if key(left[left_index]) > key(right[right_index]):
                        thing_to_sort[sorted_index] = left[left_index]
                        left_index += 1
                    else:
                        thing_to_sort[sorted_index] = right[right_index]
                        right_index += 1
                sorted_index += 1

            while left_index < len(left):
                thing_to_sort[sorted_index] = left[left_index]
                left_index += 1
                sorted_index += 1

            while right_index < len(right):
                thing_to_sort[sorted_index] = right[right_index]
                right_index += 1
                sorted_index += 1

    @staticmethod
    def my_quicksorted(thing_to_sort, key=lambda x: x, reverse=False):
        MySorts.__my_quicksort(thing_to_sort, 0, len(thing_to_sort)-1, key, reverse)
        return thing_to_sort

    @staticmethod
    def my_sorted(given_iterable, key=lambda x: x, reverse=False):
        MySorts.__my_mergesort(given_iterable, key, reverse)
        return given_iterable
