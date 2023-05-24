function myDisplayer(sum)
{
    console.log(sum)
}

async function myFunction()
{
    return "Hello";
}

myFunction().then(
  (value)=> myDisplayer(value),
  (error)=> myDisplayer(error)
);
