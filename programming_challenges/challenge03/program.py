#!/usr/bin/env python3
import sys
'''
Written by Josh Bottelberghe on Mon 17 Aug, 2020

Purpose:            Search a rotated array for a given value
General approach:   Beacuse the rotated array still has two sorted portions,
                    we can use this to modify binary search to get O(log(n))
'''

def main():

    arr    = None
    target = -1

    for l in sys.stdin:
        if not arr:
            arr = list(map(int, l.strip().split()))
        else:
            target = int(l.strip())
            rotated_binary_search(arr, target)
            arr = None

def rotated_binary_search(arr, target):
    ''' Navigate the rotation with mid left and right pointers. '''
    left = 0
    right = len(arr) - 1

    while left <= right:
        mid = (left + right) // 2

        if arr[mid] == target:
            print(target, "found at index", mid)
            return

        if arr[left] <= arr[mid]:
            # here, the left half is sorted and we can Search
            if arr[left] <= target <= arr[mid]:
                right = mid - 1
            else:
                left = mid + 1
        else:
            # here is if the right half is sorted
            if arr[mid]  <= target <= arr[right]:
                left = mid + 1
            else:
                right = mid - 1

    print(target, "was not found")




if __name__ == "__main__":
    main()
