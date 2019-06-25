
QUnit.test( "Array to object test", function( assert ) {
    let arr = [{name:'test1',value:1},{name:'test2',value:2}];
    let result = arrayToObject(arr)
    assert.ok( result.hasOwnProperty("test1"), "has property test1" );
    assert.ok( result.hasOwnProperty("test2"), "has property test2" );
    assert.ok( result.test1 === 1, "property value 1" );
    assert.ok( result.test2 === 2, "property value 2" );
})



QUnit.test( "Uniqe array by pin property", function( assert ) {
    let arr = [{pin:2},{pin:12},{pin:2}];
    let result = uniqeArr(arr)
    assert.ok( result[0].hasOwnProperty("pin"), "has property pin" );
    assert.ok( result.length === 2, "length 2" );
    assert.ok( result[1].pin === 12, "value 12 in array" );
})