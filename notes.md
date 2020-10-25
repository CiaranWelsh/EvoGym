Some general notes
------------------
- Overall 99.1% of computatino time in random network generation lies with the JIT compilation code. 
    - It seems that the JIT compiling of th emodel is the bottleneck. My question is how much time 
    is saved by JITing the model overall, when including simulation times? 
    - Since we are going to be generating lots of models it is possible that for this 
      problem JITed code is actually slower overall than non-jitted alternatives. 
    - However, when non-jitted code, obviously the simulation time will be greater 
      so its very difficult to tell. 
 - Thinking further, if I'm going to be relying heavily on HPC it may just be okay since we 
   can throw more cores at it. 
   
   
 - It actually might not have been necessary to implement the rate law parser because RR actually takes the raw string. 
 