package main

import "fmt"

func twoSum(nums []int, target int) []int {
	dict := make(map[int]int)
	for ind, val := range nums {
		if val0, ok := dict[target-val]; ok {
			return []int{val0, ind}
		}
		dict[val] = ind
	}
	return nil
}

func main() {
	nums := []int{2, 7, 11, 15}
	target := 9
	fmt.Println(twoSum(nums, target))
}
