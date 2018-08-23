public static int[] twoSum(int [] numbers, int target) {
  for(int right=numbers.length-1;right>0;right--) {
      for(int left=0;left<right;left++) {
        if(numbers[left]+numbers[right]>target)
          break;
        if(numbers[left]+numbers[right]==target) {
          return new int[] {left+1,right+1};
        }
      }
  }
  return null;
}
