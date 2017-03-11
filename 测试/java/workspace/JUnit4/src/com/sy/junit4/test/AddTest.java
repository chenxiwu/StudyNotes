package com.sy.junit4.test;

import static org.junit.Assert.*;

import org.junit.Test;

import com.sy.junit4.Add;


public class AddTest {

	@Test
	public void test() {
		int a = new Add().add(3, 5);
		assertEquals(8, a);
	}

}
