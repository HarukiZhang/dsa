from time import perf_counter as pfc
from random import randint as rdi

def random_generator(size:int, num_range:int=int(1e9)) -> tuple[list[int], int]:
    lst = []
    for _ in range(size):
        lst.append(rdi(int(-num_range), int(num_range)))
    return lst, (lst[rdi(0, size-1)] + lst[rdi(0, size-1)])

def twoSum(nums:list[int], target:int) -> list[int]:
    records = dict()
    for idx in range(len(nums)):
        val = nums[idx]
        if (target - val) in records:
            return [records[target - val], idx]
        records[val] = idx
    return False

def twoSum_1(nums:list[int], target:int) -> list[int]:
    records = dict()
    for idx, val in enumerate(nums):
        if (target - val) not in records:
            records[val] = idx
        else:
            return [records[target - val], idx]
    return False

def twoSum_nsq(nums:list[int], target:int) -> list[int]:
    ln = len(nums)
    for i in range(ln-1):
        for k in range(i+1, ln):
            if (target - nums[i]) == nums[k]:
                return [i,k]
    return False

def main():
    t0, t2 = pfc(), 0
    for i in range(300):
        nums, target = random_generator(size = rdi(0, int(1e4)), num_range = rdi(0, int(1e9)))
        t1 = pfc()
        if not twoSum(nums, target):
            print("error")
            return
        t2 += pfc() - t1
    print(f"Complete: ({t2*1000:.3f} ms) gen ({(pfc()-t0-t2)*1000:.3f} ms)")

if __name__ == "__main__":
    main()